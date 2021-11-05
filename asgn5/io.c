#include "io.h"
#include "defines.h"
#include "code.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint64_t bytes_read;
uint64_t bytes_written;
static uint8_t buf[BLOCK];
static int index = 0; //CITE: TA Eugene for the statics (tack bit in the buffer)
static uint8_t wfbuf[BLOCK];

//CITE: Professor Long
//CITE: TA Eugene for help on read byte
//CITE: TA Sloan for help on read byte
//CITE: Miles for help on read bit

/*int read_bytes(int infile, uint8_t *buf, int nbytes) { //CITE: TA Eugene for sudo
    uint64_t i = nbytes; //changing expression
    while (i != bytes_read) { //reading the specified bytes by nbytes
        uint64_t bytes = read(infile, (buf + bytes_read),
            (nbytes - bytes_read)); //buffer will take in the bytes read and nbytes will decrement
        bytes_read += bytes; //reading the bytes and incrementing bytes_read
        if (bytes == 0) { //once it reaches to the end then break
            return bytes_read;
        }
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) { //CITE: TA Eugene for sudo
    uint64_t w = nbytes; // w changes nbytes
    while (w != bytes_written) { //keep track if w does not equal to bytes_written
        uint64_t bytes = write(outfile, (buf + bytes_written),
            (nbytes - bytes_written)); //buffer takes in bytes written and nbytes decrement
        bytes_written += bytes; //bytes_written adds how many bytes written
        if (bytes == 0) { //if bytes reaches the end return bytes
            return bytes_read; //return bytes written if it read the whole file
        }
    }
    return bytes_written; //return bytes_written once it stops the while loop
}*/

int read_bytes(int infile, uint8_t *buf, int nbytes) { //CITE: TA Eugene for read_bytes sudo code & Tutor Eric
	int bytes = -1; 
	int total_bytes = 0;
	while ((total_bytes != nbytes) && (bytes != 0)){
		bytes = read(infile, buf, nbytes); //read function that read the infile
		total_bytes += bytes; //adding total bytes read
		buf += bytes; //add buffer
		nbytes -= bytes; //decrement nbytes
	}
	bytes_read += total_bytes; //read bytes will transfer to the bytes_read and return bytes_read
	return bytes_read; //returning the bytes_read
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) { //CITE: TA Eugene for write_bytes sudo code & Tutor Eric
	int bytes = -1;
	int total_bytes = 0;
	while((total_bytes != nbytes) && (bytes != 0)){
		bytes = write(outfile, buf, nbytes); //read function that wirte to the outfile
		total_bytes += bytes;  // add the bytes to total_bytes
		buf += bytes;  // this will add the bytes to the buffer
		nbytes -= bytes; //decrement the nbytes
	}
	bytes_written += total_bytes; //this is for assigning total_bytes to bytes_written
	return bytes_written; //returning bytes_written
}

bool read_bit(int infile, uint8_t *bit) { // CITE: TA Eugene & Tutor Eric
    static int end = -1;
    int bit_block = (8 * BLOCK);
    if (index == 0) { //if the buf is empty, fill it
        int bytes = read_bytes(infile, buf, BLOCK);
        if (bytes < BLOCK) {
            //set the end
            //end is marked as 1 after the last valid bits
            end = (bytes * 8) + 1;
        }
    }
    //return a bit out of a buffer
    *bit = (buf[index/8] >> (index % 8)) & 0x1;
    index = ((index + 1) / (bit_block));

    //returning true/false
    return (index == (8 * bit_block));
}

void write_code(int outfile, Code *c) { //CITE: TA Eugene & Tutor Eric
    //buffers a code
    //buffer is written when filled

    //buffer each bit into the buffer
    for (uint32_t i = 0; i < code_size(c); i += 1) { //if the bit in c-> bits at index 1
	uint8_t bit = code_get_bit(c, i);    
    	if(bit == 1){
		//set the bit
		wfbuf[index / 8] |= (0x1 << (index % 8));
	}
	else{
		//clear the bit
		wfbuf[index / 8] &= ~(0x1 << (index % 8));
    	}
	index += 1;
	if(index == BLOCK * 8){
		flush_codes(outfile);
	}
    }
    return;
}
void flush_codes(int outfile) { //CITE: TA Eugene
    //flush bits out of buffer if not empty
    uint8_t byte = 0;
    if((index % 8) == 0){
	   byte = (index / 8);
    } else {
	    byte = ((index / 8) + 1);
    }
    write_bytes(outfile, wfbuf, byte);
    return;
}
