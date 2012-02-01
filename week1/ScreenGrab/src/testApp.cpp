#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){

	finder.setup("haarcascade_frontalface_default.xml");
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	//tex.allocate(300,300, GL_RGBA);
	image.allocate(300, 300, OF_IMAGE_COLOR);
	//pixels.allocate(300, 300, OF_IMAGE_COLOR);
	
	ofSetFrameRate(30);
	
	raybans.loadImage("images/kayne.png");

}

//--------------------------------------------------------------
void testApp::update(){
	
	int w = 300;
	int h = 300;
	
	// data[] holds array of pixel data of the whole image
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		
		unsigned char r = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   //R
		data[i*4+1] = data[i*4+2];   //G
		data[i*4+2] = data[i*4+3];   //B
		data[i*4+3] = r;			 //A
	}
	
	// only if we have pixel data from the image...
	if (data!= NULL) {
		//tex.loadData(data, 300, 300, GL_RGBA);
		//tex.readToPixels(pixels);
		//image = pixels;
		image.setFromPixels(data, 300, 300, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		// look for a face in the image
		finder.findHaarObjects(image.getPixelsRef());
		
		for(int y = 0; y < h; y++) {
			for(int x = 0; x < w; x++) {
				int i = y * w + x;
				
				// run through the faces array
				for(int j = 0; j < finder.blobs.size(); j++) 
				{	
					// check if our pixel's x/y are within the face's bounding rect
					if(finder.blobs[j].boundingRect.inside(x,y))
					{
						// if true, the pixel is inside the bounding rect (ie it's a face pixel!)
						// now play with it
						
						int r = data[i*4];
						int g = data[i*4+1];
						int b = data[i*4+2];
						int a = data[i*4+3];
						
						data[i*4] = g;
						data[i*4+1] = r;
						data[i*4+2] = b;
						
					}
				}
			}
		}
		
		// update the image 
		image.setFromPixels(data, 300, 300, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();		
	}
	
	//cout << imageBelowWindow()[0] << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	// draw the updated image to the screen
	ofSetColor(255, 255, 255);
	image.draw(0,0, ofGetWidth(), ofGetHeight());
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	for(int i = 0; i < finder.blobs.size(); i++) {
		
		// draw bounding rect
		// ofNoFill();
		// ofRect(finder.blobs[i].boundingRect);
		
		// draw kayne glasses over the person's face
		// raybans.draw(finder.blobs[i].boundingRect.x + finder.blobs[i].boundingRect.width/2, finder.blobs[i].boundingRect.y + finder.blobs[i].boundingRect.width/2);

	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}