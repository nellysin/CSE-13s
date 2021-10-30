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

//CITE: Professor Long 
//CITE: TA Eugene for help on read byte
//CITE: TA Sloan for help on read byte
//CITE: Miles for help on read bit

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint64_t i = nbytes;	//changing expression
    while(i != bytes_read){ 	//reading the specified bytes by nbytes
	uint64_t bytes = read(infile, (buf+bytes_read), (nbytes-bytes_read)); //buffer will take in the bytes read and nbytes will decrement 
       	bytes_read += bytes;	//reading the bytes and incrementing bytes_read
    	if(bytes == 0){		//once it reaches to the end then break
		return bytes_read;
	}
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes){
	uint64_t w = nbytes; // w changes nbytes
	while(w != bytes_written){ //keep track if w does not equal to bytes_written
		uint64_t bytes = write(outfile, (buf+bytes_written), (nbytes-bytes_written)); //buffer takes in bytes written and nbytes decrement
		bytes_written += bytes;	//bytes_written adds how many bytes written
		if(bytes == 0){		//if bytes reaches the end return bytes
			return bytes_read; //return bytes written if it read the whole file
		}
	}
	return bytes_written; //return bytes_written once it stops the while loop
}

bool read_bit(int infile, uint8_t *bit){
	uint64_t bytes_read = read_bytes(infile, bit, BLOCK); //reading the bytes first
	uint8_t b = 0; 				// this is the index
	if(bytes_read < BLOCK){			//if the bytes_read does not reach to 0
		*bit = buf[b / 8] >> (b % 8) & 0x1;	//Finding the bit, shifting it, and and it to find the exact bit in index (CITE: Prof Long from bv8.c)
		b += 1;
		return true;
	}
	else if(b == bytes_read * 8){
		bytes_read = read_bytes(infile, (bit+bytes_read), (BLOCK-bytes_read));

	else{
		return false;
	}
}

//void read_bitTest(){
//	uint8_t bitRead = 0;
//	int infile = open("test.txt", O_RDONLY);
//	if(
//}

//void write_code(int outfile, Code *c){
//	for(int i = 0; i < BLOCK; i += 1){
//		if(read_bit){
//			c->top = bit[i]
//		}
//	}
//}



