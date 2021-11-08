#include "io.h"
#include "defines.h"
#include "code.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint64_t bytes_read; //this is for stats
uint64_t bytes_written; //this is for stats
static uint8_t buf[BLOCK];
static int index = 0; //CITE: TA Eugene for the statics (tack bit in the buffer)
static uint8_t wfbuf[BLOCK];

//CITE: Professor Long for some code in comments repo
//CITE: TA Eugene for help on read byte
//CITE: TA Sloan for help on read byte
//CITE: Miles for help on read bit

int read_bytes(int infile, uint8_t *buf,
    int nbytes) { //CITE: TA Eugene & Tutor Jason for sudo for read_bytes 10/28 section
    int bytes = 0; // taking in read
    int total_read = 0; // this is what we will be returning

    do {
        bytes = read(infile, buf + total_read, nbytes - total_read); //read bytes
        total_read += bytes; // increment read bytes
        bytes_read += bytes; //this is for for stats -- bytes_read (checking doc to include this)

    } while (bytes > 0); // this is a do while loop, as long as bytes is > 0

    return total_read; //returning te total read
}

int write_bytes(int outfile, uint8_t *buf,
    int nbytes) { //CITE: TA Eugene & Tutor Jason for sudo for write_bytes 10/28section
    int bytes = 0; //taking in the read
    int total_write = 0; //this is what we will be returning

    do {
        bytes = write(outfile, buf + total_write, nbytes - total_write); //do while loop
        total_write += bytes; //increment total write
        bytes_written += bytes; // this is for stats -- bytes_write (checking doc to include this)

    } while (bytes > 0); // this is a do while loop, as long as bytes is > 0

    return total_write; //returning total write
}

bool read_bit(int infile,
    uint8_t *bit) { // CITE: TA Eugene during 10/28 Section & Tutor Eric in 11/3 session for readbit
    index = 0;
    static int end = -1; // checking the last valid bit
    int bit_block = (BLOCK * 8);
    if (index == 0) { //if the buf is empty, fill it
        int bytes = read_bytes(infile, buf, BLOCK);
        if (bytes < BLOCK) {
            //set the end
            //end is marked as 1 after the last valid bits
            end = (bytes * 8) + 1;
        }
    }
    //return a bit out of a buffer
    *bit = (buf[index / 8] >> (index % 8)) & 0x1; // shift the bit CITE: Professor Long bv8
    index += 1; //increment the index
    if (index == bit_block) { //if the index reaches the block of bits
        index = 0; //reset the index
    }
    //returning true/false
    return (index != end);
}

void write_code(int outfile,
    Code *c) { // CITE: TA Eugene during 10/28 Section & Tutor Eric in 11/3 session for write code
    //buffers a code
    //buffer is written when filled

    //buffer each bit into the buffer
    for (uint32_t i = 0; i < code_size(c); i += 1) { //if the bit in c-> bits at index 1
        uint8_t bit = (c->bits[i / 8] >> (i % 8) & 0x1);
        if (bit == 1) {
            //set the bit
            wfbuf[index / 8] |= (0x1 << (index % 8)); //CITE: Professor Long comments repo bv32
        } else {
            //clear the bit
            wfbuf[index / 8] &= ~(0x1 << (index % 8)); //CITE: Professor Long comments repo bv32
        }
        index += 1; //increment index
        if (index == BLOCK * 8) { //if index = the number of bits in BLOCK
            write_bytes(outfile, wfbuf, BLOCK);
            index = 0;
        }
    }
    return;
}

void flush_codes(
    int outfile) { // CITE: TA Eugene during 10/28 Section & Tutor Eric in 11/3 session for flush codes
    //flush bits out of buffer if not empty
    int bytes_write = (index % 8) == 0 ? (index / 8) : (index / 8) + 1;
    //if bytes_write is (index % 8) is false (index/8) else (index/8) + 1
    write_bytes(outfile, wfbuf, bytes_write);
    return;
}
