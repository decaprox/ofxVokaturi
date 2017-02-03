#pragma once

#include "ofxVokaturi.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{
	private:
		ofSoundStream soundStream;
		ofxVokaturi vokaturi;
		ofxVokaturi::Emotions emotions;
		bool valid;
	public:
		void setup();
		void update();
		void draw();

		void audioIn(ofSoundBuffer&);
};
