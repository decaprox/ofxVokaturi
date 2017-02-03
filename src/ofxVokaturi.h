#pragma once

#include "ofMain.h"
#include "Vokaturi.h"

class ofxVokaturi : public ofThread
{
public:
	struct Emotions {
		float neutrality;
		float happiness;
		float sadness;
		float anger;
		float fear;
	};

	enum { SAMPLE_RATE = 48000, BUFFER_SIZE = 480000 };

protected:
	enum { DEFAULT_DELAY = 500 };
	
	VokaturiVoice voice;
	Emotions emotions;
	bool valid;
	unsigned delay;

	struct Buffer {
		enum { SIZE = 48000 };

		double samples[SIZE];
		uint64_t sent_samples;
		uint64_t received_samples;
	} buffer;

	void extract_emotions(void)
	{
		lock();
		if (!buffer.received_samples) {
			unlock();
			return;   // nothing recorded yet
		}
		if (buffer.received_samples > buffer.sent_samples) {
			for (int64_t isamp = buffer.sent_samples;
			     isamp < buffer.received_samples;
			     isamp++) {
				int32_t index = (int32_t)(isamp % Buffer::SIZE);
				VokaturiVoice_fill (voice, 1, &buffer.samples[index]);
			}
			buffer.sent_samples = buffer.received_samples;
		}
		unlock();

		VokaturiQuality quality;
		VokaturiEmotionProbabilities vok_emotions;

		VokaturiVoice_extract(voice, &quality, &vok_emotions);
		valid = quality.valid;
		
		if (valid) {
			lock();
			emotions.neutrality = vok_emotions.neutrality;
			emotions.happiness = vok_emotions.happiness;
			emotions.sadness = vok_emotions.sadness;
			emotions.anger = vok_emotions.anger;
			emotions.fear = vok_emotions.fear;
			unlock();
		}		
	}
	
	void threadedFunction()
	{
		while (true) {
			extract_emotions();
			sleep(delay);
		}
	}

public:
	void setDelay(unsigned _delay) { delay = _delay; }
	unsigned getDelay(void) { return delay; }
	bool isValid(void) { return valid; }

	Emotions getEmotions(void)
	{
		lock();
		Emotions _emotions = emotions;
		unlock();

		return _emotions;
	}

	void record(vector<float> &samples)
	{
		lock();

		uint64_t number = samples.size(); 
		uint64_t count = buffer.received_samples;
		uint32_t pointer = count % Buffer::SIZE;

		for (uint32_t i = 0; i < number; i++) {
			if (pointer >= Buffer::SIZE)
				pointer -= Buffer::SIZE;
			buffer.samples[pointer] = (double) samples[i];
			pointer += 1;
		}

		buffer.received_samples += number;
		unlock();
	}

	ofxVokaturi() : delay(DEFAULT_DELAY)
	{
		voice = VokaturiVoice_create (SAMPLE_RATE, BUFFER_SIZE);
		startThread();
	}

	~ofxVokaturi()
	{
		stopThread();
		VokaturiVoice_destroy(voice);
	}
};
