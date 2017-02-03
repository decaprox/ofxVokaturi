#ifndef _Pitch_h_
#define _Pitch_h_
/*
 * Pitch.h
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

typedef struct {
	double f0InHertz;
	double strength;
} Pitch;

inline static double Pitch_getValueInSemitonesRe100Hz (Pitch *me) {
	const double pitchReference_Hz = 100.0;
	const double pitch_octavesRelativeToReference = log2 (my f0InHertz / pitchReference_Hz);
	const double numberOfSemitonesPerOctave = 12.0;
	const double pitch_semitonesRelativeToReference =
		pitch_octavesRelativeToReference * numberOfSemitonesPerOctave;
	return pitch_semitonesRelativeToReference;
}

inline static bool Pitch_isValid (Pitch *me) {
	return my f0InHertz > 0.0;
}

/* End of file Pitch.h */
#endif
