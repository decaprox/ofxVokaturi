#ifndef _Cues9_h_
#define _Cues9_h_
/*
 * Cues9.h
 *
 * Copyright (C) 2016,2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2017-01-06
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

enum Cues9 {
	CUE_pitAve = 0,   // average pitch, in semitones
	CUE_pitDir,   // pitch direction, in cube-rooted semitones per second
	CUE_pitDyn,   // pitch dynamics for voiced parts, in semitones per second
	CUE_pitJit,   // jitter
	CUE_intAve,   // average intensity, in dB
	CUE_intDyn,   // intensity dynamics for voice parts, in dB per second
	CUE_intJit,   // shimmer
	CUE_spcSlo,   // spectral slope
	CUE_spcJit,
	NUMBER_OF_CUES9
};

typedef double CueStrengths9 [NUMBER_OF_CUES9];

/*
	Means and standard deviations of the cues, based on EmoDB.
*/
static double Cues9_mean [NUMBER_OF_CUES9] = { 10.0, -0.7, 46.0, 170.0, 75.0, 120.0, 120.0, -20.0, 270.0 };
static double Cues9_stdev [NUMBER_OF_CUES9] = { 6.0, 1.0, 20.0, 180.0, 3.0, 30.0, 35.0, 6.0, 80.0 };

/* End of file Cues9.h */
#endif
