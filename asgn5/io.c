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
static int end = -1; // tack the last valid bit

//CITE: Professor Long 
//CITE: TA Eugene for help on read byte
//CITE: TA Sloan for help on read byte
//CITE: Miles for help on read bit

int read_bytes(int infile, uint8_t *buf, int nbytes) { //CITE: TA Eugene for sudo
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

int write_bytes(int outfile, uint8_t *buf, int nbytes){ //CITE: TA Eugene for sudo
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


bool read_bit(int infile, uint8_t *bit){ // CITE: TA Eugene
	if(index == 0){ //if the buf is empty, fill it
		int bytes = read_bytes(infile,buf, BLOCK);
		if(bytes < BLOCK){
			//set the end
			//end is marked as 1 after the last valid bits
			end = (bytes * 8) + 1;
		}
	}
	//return a bit out of a buffer
	*bit = code_get_bit(bit, index);
	index += 1;
	
	if(index == BLOCK*8){ //when to reset the index
		index = 0;
	}
	//returning true/false
	return index != end;
}


void write_code(int outfile, Code *c){ //CITE: TA Eugene
	//buffers a code
	//buffer is written when filled 
	
	//buffer each bit into the buffer
	for(uint32_t i = 0; i < code_size(c); i += 1){ 
		buf[index] = code_get_bit(c, i);
	        if(buf[index] == 1){
			//set the bit at index
		} else{
			//clearing the bit
		}
		index += 1;
		//if buffer is filled (if index == BLOCK *8)
		if(index == BLOCK * 8){
			flush_codes(outfile);
		}
	}
}

void flush_codes(int outfile){
	//flush bits out of buffer if not empty
	if(index > 0){
		//convert index into bytes
		//write_bytes(outfile, index);
	}
}


