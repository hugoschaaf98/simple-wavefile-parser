/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
 * Ultra lightweight simple .wav LPCM decoder example
 *
 *
 * Copyright (C) 2020  HugoS (github hugoschaaf98)
 * revision ID : 2
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "wavefile.h"


/* Uncomment if you want to use the example header below */
//#define USE_EXAMPLE_HEADER 1
#ifdef USE_EXAMPLE_HEADER
const unsigned char buf[] = {	0x52, 0x49, 0x46, 0x46, 
								0xa4, 0x99, 0x01, 0x00,
								0x57, 0x41, 0x56, 0x45, 
								0x66, 0x6d, 0x74, 0x20,
								0x10, 0x00, 0x00, 0x00,
								0x01, 0x00, 0x01, 0x00,
								0x44, 0xac, 0x00, 0x00,
								0x44, 0xac, 0x00, 0x00,
								0x01, 0x00, 0x08, 0x00,
								0x64, 0x61, 0x74, 0x61,
								0x80, 0x99, 0x01, 0x00
							};
#endif


int main(int argc, char const *argv[])
{

	wheader_t header;

#ifndef USE_EXAMPLE_HEADER
	
	unsigned char buf[WAVEFILE_HEADER_SIZE] = {0};
	FILE* f = NULL;


	if(argc < 2 )
	{
		printf("%s\n","At least one argument expected");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i < argc; i++)
	{
			
		if(strcmp(argv[i]+strlen(argv[i])-4, ".wav")) continue;

		if((f = fopen(argv[i], "r")) == NULL)
		{
			fprintf(stderr, "Couldn't open <%s>\n",argv[i]);
		}

		printf("Header content of <%s>\n", argv[i]);

		fread(buf, sizeof *buf, WAVEFILE_HEADER_SIZE, f);
		fclose(f);

		f = fopen("./header.bin", "w");
		fwrite(buf, sizeof *buf, WAVEFILE_HEADER_SIZE, f);
		fclose(f),
#endif

		wavefileParseHeader(buf, &header);

		printf("channels : %u\nsampleRate : %u\nbyteRate : %u\nbytesPerSample : %u\nbitsPerSample : %u\ndataSize : %u\n",
			header.channels, 
   			header.sampleRate, 
    		header.byteRate, 
    		header.bytesPerSample, 
    		header.bitsPerSample, 
    		header.dataSize);

#ifndef USE_EXAMPLE_HEADER
	}
#endif

	return EXIT_SUCCESS;
}
