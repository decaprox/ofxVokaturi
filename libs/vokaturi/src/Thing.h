#ifndef _Thing_h_
#define _Thing_h_
/*
 * Thing.h
 *
 * Copyright (C) 2016,2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2016-01-21
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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
	The use of the macros "my" and "your" is Praat style (www.praat.org).
	They can shorten the code appreciably.
*/
#define my  me ->
#define your  you ->

#define strequ  ! strcmp
#define strnequ  ! strncmp

/* End of file Thing.h */
#endif
