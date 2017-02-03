#ifndef _Sound_h_
#define _Sound_h_
/*
 * Sound.h
 *
 * Copyright (C) 2016,2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2017-01-21
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

#include "Thing.h"

/*
	A Sound is a structure that can hold the samples of a monaural sound.

	- length
		The number of doubles required to hold the sound.

	- samplingFrequencyInHertz
		The inverse of the time step between consecutive samples.

	- samples
		The doubles that hold the sound. The length of this array is `length`.
*/
typedef struct {
	double *samples;
	int length;
	double samplingFrequencyInHertz;
} Sound;

inline static void Sound_initWithLengthAndSamplingFrequency (Sound *me, int length, double samplingFrequencyInHertz) {
	my samples = (double *) calloc (length, sizeof * my samples);
	if (my samples == NULL) {
		return;
	}
	my length = length;
	my samplingFrequencyInHertz = samplingFrequencyInHertz;
}

inline static bool Sound_isValid (Sound *me) {
	return my samples != NULL;
}

inline static void Sound_initAsSweep (Sound *me, double duration, double samplingFrequency, double endFrequency) {
	Sound_initWithLengthAndSamplingFrequency (me, duration * samplingFrequency, samplingFrequency);
	if (! Sound_isValid (me)) return;
	const double samplingPeriod = 1.0 / samplingFrequency;
	double phase = 0.0;
	for (int isamp = 0; isamp < my length; isamp ++) {
		const double time = (double) isamp / samplingFrequency;
		const double fractionThrough = time / duration;
		const double localFrequency = fractionThrough * endFrequency;
		const double dphase = 2.0 * M_PI * localFrequency * samplingPeriod;
		phase += dphase;
		my samples [isamp] = 0.9 * sin (phase);
	}
}

inline static void Sound_destroy (Sound *me) {
	if (my samples) {
		free (my samples);
		my samples = NULL;
	}
}

inline static void Sound_fillWithNuttallWindow (Sound *me) {
	const double a0 = 0.355768, a1 = -0.487396, a2 = 0.144232, a3 = -0.012604;
	const double fac1 = 2 * M_PI / (my length - 1), fac2 = 2.0 * fac1, fac3 = 3.0 * fac1;
	for (int isamp = 0; isamp < my length; isamp ++) {
		double value = a0 + a1 * cos (fac1 * isamp) + a2 * cos (fac2 * isamp) + a3 * cos (fac3 * isamp);
		my samples [isamp] = value;
		//fprintf (stderr, "window %d %g\n", isamp, my window [isamp]);
	}
}

inline static double Sound_getSum (Sound *me) {
	double sum = 0.0;
	for (int isamp = 0; isamp < my length; isamp ++) {
		sum += my samples [isamp];
	}
	return sum;
}

inline static double Sound_getSumOfSquares (Sound *me) {
	double sumOfSquares = 0.0;
	for (int isamp = 0; isamp < my length; isamp ++) {
		sumOfSquares += my samples [isamp] * my samples [isamp];
	}
	return sumOfSquares;
}

inline static double Sound_getMean (Sound *me) {
	double sum = Sound_getSum (me);
	return sum / my length;
}

inline static void Sound_addConstant (Sound *me, double constant) {
	for (int isamp = 0; isamp < my length; isamp ++) {
		my samples [isamp] += constant;
	}
}

inline static void Sound_subtractMean (Sound *me) {
	double mean = Sound_getMean (me);
	Sound_addConstant (me, - mean);
}

/**
	@pre   your length >= my length
*/
inline static void Sound_multiplyByOtherSound (Sound *me, Sound *you) {
	for (int isamp = 0; isamp < my length; isamp ++) {
		my samples [isamp] *= your samples [isamp];
	}
}

/**
	@pre   your length >= my length
	@pre   your samples [1..my length] != 0.0
*/
inline static void Sound_divideByOtherSound (Sound *me, Sound *you) {
	for (int isamp = 0; isamp < my length; isamp ++) {
		my samples [isamp] /= your samples [isamp];
	}
}

inline static int Sound_getBestSpectrumLength (Sound *me) {
	int bestSpectrumLength = 2;
	while (bestSpectrumLength < my length)
		bestSpectrumLength *= 2;
	return bestSpectrumLength;
}

/* End of file Sound.h */
#endif
