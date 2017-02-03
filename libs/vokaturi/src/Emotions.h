#ifndef _Emotions_h_
#define _Emotions_h_
/*
 * Emotions.h
 *
 * Copyright (C) 2016,2017 Paul Boersma, Johnny Ip, Toni Gojani
 * version 2017-01-01
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

#include <assert.h>

enum Emotions {
	EMOTION_Neu = 0,   // neutrality
	EMOTION_Hap,   // happiness
	EMOTION_Sad,   // sadness
	EMOTION_Ang,   // anger
	EMOTION_Fea,   // fear
	NUMBER_OF_EMOTIONS
};

typedef double EmotionProbabilities [NUMBER_OF_EMOTIONS];

inline static void EmotionProbabilities_normalize (EmotionProbabilities emotionProbabilities) {
	double sumOfProbabilities = 0.0;
	for (int emotion = 0; emotion < NUMBER_OF_EMOTIONS; emotion ++) {
		sumOfProbabilities += emotionProbabilities [emotion];
	}
	for (int emotion = 0; emotion < NUMBER_OF_EMOTIONS; emotion ++) {
		emotionProbabilities [emotion] /= sumOfProbabilities;
	}
}

inline static int EmotionProbabilities_getWinner (EmotionProbabilities emotionProbabilities) {
	int winner = -1;
	double probability = 0.0;
	for (int emotion = 0; emotion < NUMBER_OF_EMOTIONS; emotion ++) {
		if (emotionProbabilities [emotion] > probability) {
			winner = emotion;
			probability = emotionProbabilities [emotion];
		}
	}
	assert (winner >= 0);
	return winner;
}

inline static void EmotionProbabilities_weigh (
	EmotionProbabilities emotionProbabilities,
	EmotionProbabilities relativeEmotionProbabilities)
{
	for (int emotion = 0; emotion < NUMBER_OF_EMOTIONS; emotion ++) {
		emotionProbabilities [emotion] *= relativeEmotionProbabilities [emotion];
	}
	EmotionProbabilities_normalize (emotionProbabilities);
}

/* End of file Emotions.h */
#endif
