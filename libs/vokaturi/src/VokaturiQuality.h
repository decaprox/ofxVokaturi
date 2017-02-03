#ifndef _VokaturiQuality_h_
#define _VokaturiQuality_h_
/*
 * VokaturiQuality.h
 *
 * Copyright (C) 2016,2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2.0, 2017-01-13
 *
 * This code is part of OpenVokaturi and VokaturiPlus.
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
 * If you use this file with OpenVokaturi,
 * you should have received a copy of the GNU General Public License
 * along with this software. If not, see http://www.gnu.org/licenses/.
 */

#include "Thing.h"
#include "Vokaturi.h"

inline static void VokaturiQuality_error (VokaturiQuality *me) {
	my valid = false;
	my num_frames_analyzed = 0;
	my num_frames_lost = 0;
}

/* End of file VokaturiQuality.h */
#endif
