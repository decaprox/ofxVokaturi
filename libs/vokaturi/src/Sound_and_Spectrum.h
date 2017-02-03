#ifndef _Sound_and_Spectrum_h_
#define _Sound_and_Spectrum_h_
/*
 * Sound_and_Spectrum.h
 *
 * Copyright (C) 2016 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2016-12-27
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
#include "Spectrum.h"

static void Sound_into_Spectrum (Sound *me, Spectrum *thee) {
	for (int isamp = 0; isamp < my length; isamp ++) {
		thy samples [isamp] = my samples [isamp];
	}
	for (int isamp = my length; isamp < thy length; isamp ++) {
		thy samples [isamp] = 0.0;
	}
	drftf1 (thy length, thy samples, thy smallCache, thy bigCache, thy splitCache);
}

static void Spectrum_into_Sound (Spectrum *me, Sound *thee) {
	drftb1 (my length, my samples, my smallCache, my bigCache, my splitCache);
	for (int isamp = 0; isamp < thy length; isamp ++) {
		thy samples [isamp] = my samples [isamp];
	}
}

/* End of file Sound_and_Spectrum.h */
#endif
