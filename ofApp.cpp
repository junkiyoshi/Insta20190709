#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 3);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	for (auto& triangle : this->triangles) {

		auto avg = glm::vec3(triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto param = (int)(ofRandom(750) + ofGetFrameNum()) % 750;
		auto tmp_radius = 0;
		auto rotate = 0;
		auto alpha = 255.f;
		if (param > 600) {

			tmp_radius = ofMap(param, 600, 750, 0, 600);
			rotate = ofMap(param, 600, 750, 0, 360);
			alpha = rotate = ofMap(param, 600, 750, 255, 0);
		}
		else if (param < 150) {

			alpha = ofMap(param, 0, 150, 0, 255);
		}

		auto tmp_avg = avg + glm::vec3(0, tmp_radius, 0);

		ofPushMatrix();
		ofTranslate(tmp_avg);
		ofRotateX(rotate);
		ofRotateY(rotate);

		vector<glm::vec3> vertices;
		for (int j = 0; j < 3; j++) {

			glm::vec3 location = glm::vec3(triangle.getVertex(j).x, triangle.getVertex(j).y, triangle.getVertex(j).z) - avg;

			vertices.push_back(location * 0.8);
		}
		
		ofFill();
		ofSetColor(39, alpha);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}