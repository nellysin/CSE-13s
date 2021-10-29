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
//CITE: TA Eugene for sudo code
//CITE: TA Sloan for help on read byte
//CITE: Miles for help on read bit

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint64_t i = nbytes;	//changing expression
    while(i != bytes_read){ 	//reading the specified bytes by nbytes
	uint64_t bytes = read(infile, (buf+bytes_read), (nbytes-bytes_read)); //buffer will take in the bytes read and nbytes will decrement 
       	bytes_read += bytes;	//reading the bytes and incrementing bytes_read
    	if(bytes == 0){		//once it reaches to the end then break
		break;
	}
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes){
	uint64_t w = nbytes;
	while(w != bytes_written){
		uint64_t bytes = write(outfile, (buf+bytes_written), (nbytes-bytes_written));
		bytes_written += bytes;
		if(bytes == 0){
			break;
		}
	}
	return bytes_written;
}

bool read_bit(int infile, uint8_t *bit){
        uint64_t bytes = read_bytes(infile, (bit+bytes_read), (BLOCK-bytes_read));	
	uint8_t b = 0;
	if()
	*bit = buf[b / 8] >> (b % 8) & 0x1;
	if(bytes == 0){
		return false;
	}else{
		bytes_read += bytes;
		bit->buf[b / 8] >> (b % 8) & 0x1;	//CITE: Prof Long for bv8.c
		b += 1;
		return true;
	}
}

//void write_code(int outfile, Code *c){
//	for(int i = 0; i < BLOCK; i += 1){
//		if(read_bit){
//			c->top = bit[i]
//		}
//	}
//}



