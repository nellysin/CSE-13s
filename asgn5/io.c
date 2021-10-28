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

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint64_t i = nbytes;
    while(i != bytes_read){ 	//reading the specified bytes by nbytes
	uint64_t bytes = read(infile, (buf+bytes_read), (nbytes-bytes_read));
       	bytes_read += bytes;	//reading the bytes and incrementing bytes_read
    	if(bytes == 0){
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
	int b = BLOCK;
	if(b == 0){
		return false;
	}
	else{
		int read = read_bytes(infile, buf, b);
		if(read != 0){
			bit = &buf[b];
			b -= 1;
		}
		return true;
	}

}

