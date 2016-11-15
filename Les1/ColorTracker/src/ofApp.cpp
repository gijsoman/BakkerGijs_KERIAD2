#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT, true);

	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hueImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	valImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	satImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}

//--------------------------------------------------------------
void ofApp::update(){
	grabber.update();
	//only change something when there is a new webcam frame so it doesn't do to much work
	if (grabber.isFrameNew())
	{
		rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();

		hsvImage.convertToGrayscalePlanarImages(hueImage, satImage, valImage);

		for (int i = 0; i < GRABBER_WIDTH*GRABBER_HEIGHT; i++)
		{
			if (ofInRange(hueImage.getPixels()[i], selectedHue-HUE_MARGIN, selectedHue + HUE_MARGIN))
			{
				filtered.getPixels()[i] = 255;
			}
			else
			{
				filtered.getPixels()[i] = 0;
			}
		}
		filtered.flagImageChanged();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	rgbImage.draw(640,0);

	hsvImage.draw(0, 0);
	hueImage.draw(0, 240);
	satImage.draw(320, 240);
	valImage.draw(640, 240);
	filtered.draw(0, 480);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	selectedHue = hueImage.getPixels()[y*GRABBER_WIDTH + x];
	cout << "Selected: " << selectedHue << endl;
}

