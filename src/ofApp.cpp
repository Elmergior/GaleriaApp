#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(20);

	// GL_REPEAT for texture wrap only works with NON-ARB textures //
	ofDisableArbTex();
	texture.loadImage("of.png");
	texture.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
	vidGrabber.initGrabber(640, 480, true);

	float width     = ofGetWidth() * .12;
	float height    = ofGetHeight() * .12;

	icoSphere.setRadius( width );
	mode = 0;
	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
	pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

	pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
	pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

	pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
	pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );

	// shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 120 );
	// the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));

	ofSetSphereResolution(24);
}

//--------------------------------------------------------------
void ofApp::update(){
	pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
	pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
		ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

	pointLight3.setPosition(
		cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
		sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
		cos(ofGetElapsedTimef()*.2) * ofGetWidth()
		);

	//ofSetWindowTitle("Framerate: "+ofToString(ofGetFrameRate(), 0));
	if(mode == 2 || ofGetElapsedTimef() < 10) {
		vidGrabber.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);

	if(bMousePressed) {
		spinX = spinY = 0.0f;
	}

	ofEnableDepthTest();

	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	pointLight3.enable();

	material.begin();


	ofSetColor(180);
	ofNoFill();
	ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth());
	if(mode == 1 || mode == 3) texture.getTextureReference().bind();
	if(mode == 2) vidGrabber.getTextureReference().bind();
	// ICO Sphere //
	icoSphere.setPosition(ofGetWidth()*.2, ofGetHeight()*.75, 0);
	icoSphere.rotate(spinX, 1.0, 0.0, 0.0);
	icoSphere.rotate(spinY, 0, 1.0, 0.0);

	if(mode == 3) {
		triangles = icoSphere.getMesh().getUniqueFaces();
	}

	if(bFill) {
		ofFill();
		ofSetColor(255);

		if(mode == 3) {
			float angle = (ofGetElapsedTimef() * 1.4);
			ofVec3f faceNormal;
			for(int i = 0; i < triangles.size(); i++ ) {
				float frc = ofSignedNoise(angle* (float)i * .1, angle*.05) * 4;
				faceNormal = triangles[i].getFaceNormal();
				for(int j = 0; j < 3; j++ ) {
					triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * frc );
				}
			}
			icoSphere.getMesh().setFromTriangles( triangles );
		}

		icoSphere.draw();
	}
	if(bWireframe) {
		ofNoFill();
		ofSetColor(0, 0, 0);
		if(!bFill) ofSetColor(255);
		icoSphere.setScale(1.01f);
		icoSphere.drawWireframe();
		icoSphere.setScale(1.f);
	}
	ofDisableDepthTest();

	ofFill();
	ofSetColor(0);
	ofRect(icoSphere.getPosition().x-154, icoSphere.getPosition().y + 120, 168, 24);
	ofSetColor(255);
	ofDrawBitmapString("ofIcoSpherePrimitive", icoSphere.getPosition().x-150, icoSphere.getPosition().y+136 );

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
