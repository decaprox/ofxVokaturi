#ifndef _Sound_save_h_
#define _Sound_save_h_
/*
 * Sound_save.h
 *
 * Copyright (C) 2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2017-01-23
 *
 * This code is part of OpenVokaturi.
 *
 * OpenVokaturi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * OpenVokaturi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software. If not, see http://www.gnu.org/licenses/.
 */

#include "Sound.h"

inline static void fwriteUint32LE (uint32_t x, FILE *f) {
	char bytes [4];
	bytes [3] = (char) (x >> 24);
	bytes [2] = (char) (x >> 16);
	bytes [1] = (char) (x >> 8);
	bytes [0] = (char) x;
	fwrite (bytes, sizeof (char), 4, f);
}

inline static void fwriteUint16LE (uint16_t x, FILE *f) {
	char bytes [2];
	bytes [1] = (char) (x >> 8);
	bytes [0] = (char) x;
	fwrite (bytes, sizeof (char), 2, f);
}

inline static int Sound_saveAsWavFile (Sound *me, const char *fileName) {
	FILE *f = fopen (fileName, "wb");
	if (f == NULL) {
		fprintf (stderr, "VokaturiWavFile error: cannot open file %s.\n", fileName);
		return 1;
	}
	fwrite ("RIFF", sizeof (char), 4, f);
	const uint32_t formatSize = 16;
	const int numberOfBytesPerSamplePoint = 2;
	const int numberOfChannels = 1;
	const uint32_t dataSize = my length * numberOfBytesPerSamplePoint * numberOfChannels;
	const uint32_t sizeOfRiffChunk = 4 + (12 + formatSize) + (4 + dataSize);
	fwriteUint32LE (sizeOfRiffChunk, f);
	fwrite ("WAVEfmt ", sizeof (char), 8, f);
	fwriteUint32LE (formatSize, f);
	const uint16_t WAVE_FORMAT_PCM = 1;
	fwriteUint16LE (WAVE_FORMAT_PCM, f);
	fwriteUint16LE (numberOfChannels, f);
	fwriteUint32LE (my samplingFrequencyInHertz, f);
	const uint32_t numberOfBytesPerSecond = my samplingFrequencyInHertz * numberOfBytesPerSamplePoint * numberOfChannels;
	fwriteUint32LE (numberOfBytesPerSecond, f);
	const uint16_t blockAlignment = numberOfBytesPerSamplePoint * numberOfChannels;
	fwriteUint16LE (blockAlignment, f);
	fwriteUint16LE (numberOfBytesPerSamplePoint * 8, f);
	/* Data Chunk: 8 bytes + samples. */
	fwrite ("data", sizeof (char), 4, f);
	fwriteUint32LE (dataSize, f);
	for (int isamp = 0; isamp < my length; isamp ++) {
		double value_real = my samples [isamp] * 32768.0;
		int16_t value_int = ( value_real < -32768.0 ? -32768 : value_real > 32767.0 ? 32767 :
			(int16_t) (value_real + 0.5) );
		fwriteUint16LE ((uint16_t) value_int, f);
	}
	fclose (f);
	return 0;
}

inline static void test_Sound_saveAsWavFile () {
	Sound sound;
	Sound_initAsSweep (& sound, 10.0, 44100.0, 22000.0);
	Sound_saveAsWavFile (& sound, "/Users/pboersma/Desktop/kanweg.wav");
}

/* End of file Sound_save.h */
#endif
