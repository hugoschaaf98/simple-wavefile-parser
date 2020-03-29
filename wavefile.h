/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
 * Ultra lightweight simple .wav LPCM decoder
 * Originaly develop for AVR 8bits targets
 *
 * Copyright (C) 2020  HugoS (github hugoschaaf98)
 * revision ID : 5
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

#ifndef WAVEFILE_H
#define WAVEFILE_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Wavefile structuration
 *      data identifier       offset (in byte)
 */
#define FILE_BLOCK_ID       	0x00
#define FILE_BLOCK_SIZE       	0x04
#define FILE_FORMAT           	0x08
#define FORMAT_BLOCK_ID       	0x0C
#define FORMAT_BLOCK_SIZE      	0x10
#define SAMPLE_FORMAT         	0x14
#define NUM_CHANNELS          	0x16
#define SAMPLE_RATE		      	0x18
#define BYTE_RATE	          	0x1C
#define BYTE_PER_SAMPLE        	0x20
#define BITS_PER_SAMPLE       	0x22
#define DATA_BLOCK_ID       	0x24
#define DATA_BLOCK_SIZE        	0x28
#define DATA_START_OFFSET		0x2C

#define WAVEFILE_HEADER_SIZE  	0x2C /* 40 bytes long */
#define ID_SIZE               	0x04 /* size of each block Id */
#define WAVEFILE_FORMAT_ID    	"WAVE"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* four character compare */
#define FCC(c1,c2,c3,c4)	(((uint32_t)c4<<24)+((uint32_t)c3<<16)+((uint32_t)c2<<8)+(uint32_t)c1)
/* load little endian word/dword */
#define LD_UI16(p)		    (((uint16_t)*(p+1)<<8)+(uint16_t)*p)
#define LD_UI32(p)			(((uint32_t)*(p+3)<<24)+((uint32_t)*(p+2)<<16)+((uint32_t)*(p+1)<<8)+(uint32_t)*p)
#define pos(buf, offset)    (buf+offset)


/* simple wavefile LPCM header data structure */
typedef struct
{
	uint16_t channels;
    uint32_t sampleRate, byteRate;
    uint16_t bytesPerSample, bitsPerSample;
    uint32_t dataSize;
} wheader_t;



/* const unsigned char* buf : buffer which contains at least the whole wavefile header data to parse
 * wheader_t* h : a pointer to a wheader_t structure to retreive parsed data
 */
static inline
unsigned int wavefileParseHeader(const unsigned char* buf, wheader_t* h)
{
	/* check file format */
	if ( LD_UI32(pos(buf, FILE_FORMAT)) != FCC('W','A','V','E') ) return 0;
    if ( LD_UI32(pos(buf, FORMAT_BLOCK_ID)) != FCC('f','m','t',' ') ) return 0;    /* fmt chunk */
    if ( LD_UI32(pos(buf, FORMAT_BLOCK_SIZE)) != 16 ) return 0;        /* Chunk size, 16 is for LPCM files (we want only lpcm for now) */
    if ( LD_UI16(pos(buf,SAMPLE_FORMAT)) != 1 ) return 0;  /* double check coding type (LPCM) */

	/* retreive recording properties */
    h->channels = LD_UI16( pos(buf,NUM_CHANNELS));   /* Check channels (1 - 2 ...) */
    h->sampleRate = LD_UI32( pos(buf,SAMPLE_RATE));    /* Check sampling frequency (8kHz-48kHz) */
    h->byteRate = LD_UI32( pos(buf,BYTE_RATE));
    h->bytesPerSample = LD_UI16( pos(buf,BYTE_PER_SAMPLE));
    h->bitsPerSample = LD_UI16( pos(buf,BITS_PER_SAMPLE));  /* Check resolution (8 bit) */
    return (h->dataSize = LD_UI32( pos(buf,DATA_BLOCK_SIZE)));
}

#ifdef __cplusplus
}
#endif

#endif
