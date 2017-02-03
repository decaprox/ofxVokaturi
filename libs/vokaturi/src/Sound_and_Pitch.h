#ifndef _Sound_and_Pitch_h_
#define _Sound_and_Pitch_h_
/*
 * Sound_and_Pitch.h
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

#include "Sound.h"
#include "Pitch.h"

inline static void Sound_autocorrelation_into_Pitch (Sound *me, Pitch *you, double fmin, double fmax) {
	double dt = 1.0 / my samplingFrequencyInHertz;
	int imin = (int) ceil (1.0 / (fmax * dt));
	int imax = (int) floor (1.0 / (fmin * dt));
	if (imin <= 0) {
		imin = 1;
	}
	if (imax >= my length / 2 - 1) {
		imax = my length / 2 - 2;
	}
	double maximum = -1e300;
	double bestLag_samples = 0.0;
	for (int ilag = imin; ilag <= imax; ilag ++) {
		double octaveCost = 0.03;
		double left = my samples [ilag - 1];
		double mid = my samples [ilag];
		double right = my samples [ilag + 1];
		if (mid > 0.0 && mid >= left && mid >= right)
		{
			/*
				We found a local maximum.
				Perform a parabolic interpolation, following
				http://www.fon.hum.uva.nl/praat/manual/vector_peak_interpolation.html
			*/
			double dy = 0.5 * (right - left);
			double d2y = 2.0 * mid - left - right;
			if (d2y != 0.0) {
				double lag_samples = (double) ilag + dy / d2y;
				double localMaximum = (mid + 0.5 * dy * dy / d2y) / my samples [0] - octaveCost * log2 (lag_samples);
				if (localMaximum > maximum) {
					maximum = localMaximum;
					bestLag_samples = lag_samples;
				}
			}
		}
	}
	if (bestLag_samples == 0.0) {
		your f0InHertz = 0.0;   // this signals failure
		your strength = 0.0;
	} else {
		double bestLag_seconds = dt * bestLag_samples;
		your f0InHertz = 1.0 / bestLag_seconds;
		your strength = maximum;
	}
}

/* End of file Sound_and_Pitch.h */
#endif
