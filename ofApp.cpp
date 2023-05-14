#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	this->number_of_targets = 360;
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->target_list.clear();
	this->color_list.clear();

	for (int x = 45; x < ofGetWindowWidth(); x += 90) {

		for (int i = 0; i < 45; i++) {

			auto y = ofGetWindowHeight() * 0.5 + ofMap(ofNoise(x * 0.01 + i * 0.01 + ofGetFrameNum() * 0.02), 0, 1, -360, 360);

			auto target = glm::vec2(x, y);
			this->target_list.push_back(target);

			this->color_list.push_back(glm::vec3(1, 1, 1));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->target_list[0].x, this->number_of_targets);
	this->shader.setUniform3fv("colors", &this->color_list[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}