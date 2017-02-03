#include "ofApp.h"

/*
 * Settings
 */

/* Audio */
#define BUFFER_SIZE 256
#define SAMPLE_RATE ofxVokaturi::SAMPLE_RATE

//--------------------------------------------------------------
void ofApp::setup(){
	ofSoundStreamSettings settings;

	soundStream.printDeviceList();

	auto devices = soundStream.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setOutDevice(devices[0]);
	}

	settings.setInListener(this);
	settings.sampleRate = SAMPLE_RATE;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 1;
	settings.bufferSize = BUFFER_SIZE;
	soundStream.setup(settings);

	ofBackground(53, 53, 53);
}

//--------------------------------------------------------------
void ofApp::update(){
	valid = vokaturi.isValid();
	if(valid)
		emotions = vokaturi.getEmotions();
}

//--------------------------------------------------------------

#define DRAW_EMO(__emo, y)						\
	ofDrawBitmapString(#__emo + ofToString(": ")			\
		+ ofToString(emotions.__emo, 4), 4, (1 + y) * 18)

void ofApp::draw(){
	ofDrawBitmapString(ofToString("VOKATURI STATUS: ")
		+ (valid ? "VALID" : "NOT VALID"), 4, 18);
	DRAW_EMO(neutrality, 1);
	DRAW_EMO(happiness, 2);
	DRAW_EMO(sadness, 3);
	DRAW_EMO(anger, 4);
	DRAW_EMO(fear, 5);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input)
{
	vokaturi.record(input.getBuffer());
}
