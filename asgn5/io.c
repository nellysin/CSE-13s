#include "io.h"
#include "code.h"

#include <stdio.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t bytes_read;
uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes){
	while(buf[nbytes] > 0){
		bytes_read += read(infile, buf, nbytes);
		nbytes -= 1;
	}
	return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes){
	while(buf[nbytes] > 0){
		write(outfile, buf, nbytes);
	}
	return outfile;
}

int main(void){
	uint8_t buf[256];
	int infile = open("test.txt", O_RDONLY);
	read_bytes(infile, buf, 256);
	printf("Bytes read: %"PRIu64" ", bytes_read);
	return 0;
}
