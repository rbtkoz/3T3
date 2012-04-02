#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("Cells_expressionre.mov");
        vidPlayer.play();
	#endif

    colorImg.allocate(320,240);
	greenImage.allocate(320,240);
    redImage.allocate(320,240);
    yellowImage.allocate(320,240);


	bLearnBakground = false; // set to false results in better precision
	threshold = 160;
    green = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;
    float green = -1;
    int counter = 0;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif
 
	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif
        
        // do it for green
        
        unsigned char * pixels = colorImg.getPixels();
        unsigned char * greenPixels = new unsigned char[320*240];
        unsigned char * redPixels = new unsigned char[320*240];
        unsigned char * yellowPixels = new unsigned char[320*240];
//       
        for(int i = 0; i < 320*240; i++)
        {
            int r = pixels[i * 3];
            int g = pixels[i * 3 + 1];
            int b = pixels[i * 3 + 2];
            //green += g;
            // check green
            
            if(g > threshold)
            
            {   
                greenPixels[i] = 255;
               green += g;
                counter++;
            }
            else
            {
                greenPixels[i] = 0;
            }
            // check red
            if(r > threshold)  {
                
           
                redPixels[i] = 255;
            }
            else
            {
                redPixels[i] = 0;
            }
            
            // check yellow
            if (g > threshold - 30 && r >threshold - 20)
            {
                yellowPixels[i] = 255;
            }
            else
            {
                yellowPixels[i] = 0;
            }
        
       
        
        }

        greenImage.setFromPixels(greenPixels, 320, 240);
        redImage.setFromPixels(redPixels, 320, 240);
        yellowImage.setFromPixels(yellowPixels, 320, 240);    
//      
        // do it again for red and blue
    
        
        
        
		// take the abs value of the difference between background and incoming and then threshold:
		//grayDiff.absDiff(grayBg, grayImage);
		//grayImage.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		}
        // also, find holes is set to true so we will get interior contours as well....
		contourFindergreen.findContours(greenImage, 20, (340*240)/3, 10, true);	// find holes
        contourFinderred.findContours(redImage, 20, (340*240)/3, 10, true);  
        contourFinderyellow.findContours(yellowImage, 20, (340*240)/3, 10, true);  
    if (bNewFrame){
        printf("----------- %f--------------",green/counter);    
    
        
	}

    

}
//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
	colorImg.draw(0,0);
    
    
	
    // draw the green image
    greenImage.draw(320,0);
	ofFill();
	ofSetHexColor(0x333333);
	ofRect(320,0,320,240);
	ofSetHexColor(0xffffff);
    for (int i = 0; i < contourFindergreen.nBlobs; i++){
        contourFindergreen.blobs[i].draw(320,0);
        
    }
    
    
    // draw the red image (this should be replaced with redImage)
   
    redImage.draw(320,250);
	ofFill();
	ofSetHexColor(0x333333);
	ofRect(320,250,320,240);
	ofSetHexColor(0xffffff);
    
    for (int i = 0; i < contourFinderred.nBlobs; i++)
    {
        contourFinderred.blobs[i].draw(320,250);
    }

    
        
	//draw the yellow image
    ofSetHexColor(0xffffff);
    yellowImage.draw(320,500);
	ofFill();
	ofSetHexColor(0x333333);
	ofRect(320,500,320,240);
	ofSetHexColor(0xffffff);
    for (int i = 0; i < contourFinderyellow.nBlobs; i++)
    {
        contourFinderyellow.blobs[i].draw(320,500);
    
    }
    
    ofSetHexColor(0xffffff);
    char reportStrgreen[1024];
	sprintf(reportStrgreen,"green :: G1 -> S ");
	ofDrawBitmapString(reportStrgreen, 680, 100);
    
    
    ofSetHexColor(0xffffff);
    char reportStrred[1024];
	sprintf(reportStrred,"red :: G2 -> M");
	ofDrawBitmapString(reportStrred, 680, 350);
    
    
    ofSetHexColor(0xffffff);
    char reportStryellow[1024];
	sprintf(reportStryellow,"yellow S");
	ofDrawBitmapString(reportStryellow, 680, 600);
    
    

}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
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
