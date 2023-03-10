#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	bool flag = true;
	for (int x = -270; x <= 270; x += 180) {

		auto base_location = glm::vec2(x, 150);
		auto target_location = glm::vec2(x, -150);
		auto distance = target_location - base_location;
		auto len = glm::length(distance);

		vector<glm::vec2> vertices;
		for (int d = 0; d <= len; d++) {

			auto location = base_location + glm::normalize(distance) * d;

			auto gap = abs(len * 0.5 - d);
			auto power = gap < len * 0.35 ? 1 : ofMap(gap, len * 0.35, len * 0.5, 1, 0);

			if (flag) {

				auto noise_x = ofMap(ofNoise(location.x * 0.05, location.y * 0.015 + ofGetFrameNum() * 0.05), 0, 1, -50, 50);
				location += glm::vec2(noise_x * power, 0);
			}
			else {

				auto noise_x = ofMap(ofNoise(location.x * 0.05, location.y * 0.015 - ofGetFrameNum() * 0.05), 0, 1, -50, 50);
				location += glm::vec2(noise_x * power, 0);
			}

			vertices.push_back(location);
		}

		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofFill();
		ofDrawCircle(vertices.front(), 6);
		ofDrawCircle(vertices.back(), 6);

		flag = !flag;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}