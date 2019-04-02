#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Cells
    for(int i=0; i<9; i++){
        tempc = Cell(poses[i], initClr, tVec[i%3], HzVec[i/3]);
        cells.push_back(tempc);
    }
    
    
    // Dashboard
    red = 233; blue = 233; green = 233;
    hideGUI = false;
    bdrawGrid = false;
    bdrawPadding = false;
    
    ddl = NULL;
    textInput = NULL;
    img = new ofImage("orange.png");
    buffer = new float[256];
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
    setGUI1();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0; i<9; i++){
        cells[i].update();
    }
    
    aud.setVolume(vol);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(60, 60, 60, 255);
    
    ofSetColor(red, green, blue);
    ofDrawRectangle(10.0f, 780.0f, 60.0f, 60.0f);

    
    // draw cells
    for(int i=0; i<9; i++){
        cells[i].draw();
    }
    
    cout << lowMin << endl;

}


//--------------------------------------------------------------
void ofApp::exit()
{
    gui1->saveSettings("gui1Settings.xml");
    
    delete gui1;
    
    delete[] buffer;
    delete img;
}

//--------------------------------------------------------------
void ofApp::drawGrid(float x, float y)
{
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    for(int i = 0; i < h; i+=y)
    {
        ofDrawLine(0,i,w,i);
    }
    
    for(int j = 0; j < w; j+=x)
    {
        ofDrawLine(j,0,j,h);
    }
}

//--------------------------------------------------------------
void ofApp::setGUI1()
{
    gui1 = new ofxUISuperCanvas("DASHBOARD");
    gui1->addSpacer();
    gui1->addLabel("Press 'h' to Hide Panel", OFX_UI_FONT_SMALL);
    
    gui1->addSpacer();
    gui1->setGlobalButtonDimension(64);
    gui1->addImageButton("LOADAUD", "img/planemap.png", false);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui1->addImageButton("PLAYPAUSE", "img/factal.png", false);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui1->addLabel("WAVEFORM DISPLAY", OFX_UI_FONT_SMALL);
    gui1->addWaveform("WAVEFORM", buffer, 256, 0.0, 1.0);
    
    gui1->addSpacer();
    gui1->addLabel("VOLUME");
    gui1->addSlider("VOL", 0.2, 0.89, &vol)->setTriggerType(OFX_UI_TRIGGER_ALL);
    
    
    // Hz range sliders
    gui1->addSpacer();
    gui1->addLabel("\n");
    gui1->addLabel("Hz RANGE SLIDERS");
    gui1->addRangeSlider("LOW", lowMin, highMax, &lowMin, &midMin);
    gui1->addRangeSlider("MEDIUM", lowMin, highMax, midMin, highMin);
    gui1->addRangeSlider("HIGH", lowMin, highMax, highMin, highMax);
    gui1->addSpacer();
    
    
    //string textString = "This widget is a text area widget. Use this when you need to display a paragraph of text. It takes care of formatting the text to fit the block.";
    
    //gui1->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
    
    gui1->addLabel("\n");
    gui1->addSpacer();
    gui1->setGlobalButtonDimension(64);
    gui1->addImageButton("LOADIMG", "img/orange.png", false);
    gui1->addLabel("IMAGE SAMPLER", OFX_UI_FONT_MEDIUM);
    gui1->addImageSampler("SAMPLER", img);
    

    
    // final settings
    gui1->setPosition(10, 10);
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
}

//---------------------------------------------------------------
void ofApp::setGUI2()
{
    gui2 = new ofxUISuperCanvas("");
    gui2->setDimensions(800.0f, 800.0f);
    
    //gui2->addLabel("AMPLITUDE         FREQUENCY         TEXTURE");
    //gui2->addSpacer();
    gui2->setGlobalButtonDimension(250);
    //gui2->addImageButton("IMAGEBTN", "GUI/images/App.png", false);
    
    gui2->addToggleMatrix("MATRIX", 3, 3);
    
    //gui2->set
    //gui2->addToggle("", false);
    //gui2->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    //gui2->addToggle("", false);
    
    
    // final settings
    gui2->setPosition(230, 10);
    //gui2->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
}


//---------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.getName();
    int kind = e.getKind();
    cout << "got event from: " << name << endl;
    if(kind == OFX_UI_WIDGET_NUMBERDIALER)
    {
        ofxUINumberDialer *n = (ofxUINumberDialer *) e.widget;
        cout << n->getValue() << endl;
    }
    
    if(name == "SAMPLER")
    {
        ofxUIImageSampler *is = (ofxUIImageSampler *) e.widget;
        ofColor clr = is->getColor();
        red = clr.r;
        blue = clr.b;
        green = clr.g;
    }
    else if(name == "BUTTON")
    {
        ofxUIButton *button = (ofxUIButton *) e.getButton();
        bdrawGrid = button->getValue();
    }
    else if(name == "TOGGLE")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
        bdrawGrid = toggle->getValue();
        if(textInput != NULL)
        {
            textInput->setFocus(bdrawGrid);
        }
    }
    else if(name == "RADIO VERTICAL")
    {
        ofxUIRadio *radio = (ofxUIRadio *) e.widget;
        cout << radio->getName() << " value: " << radio->getValue() << " active name: " << radio->getActiveName() << endl;
    }
    else if(name == "TEXT INPUT")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
        }
        string output = ti->getTextString();
        cout << output << endl;
    }
    else if(name=="LOADAUD")
    {
        //cout << "LOAD AUD" << endl;
        loadAudFile();
    }
    else if(name=="PLAYPAUSE")
    {
        audToggle();
    }
    else if(name=="VOL")
    {
        
        
        
    }
    else if(name=="LOADIMG")
    {
        //cout << "LOAD AUD" << endl;
        loadImgFile();
    }
}


//--------------------------------------------------------------
void ofApp::loadImgFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    string path = result.getPath();
    //cout << path << endl;
    
    img->load(path);
}


//--------------------------------------------------------------
void ofApp::loadAudFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    string path = result.getPath();
    //cout << path << endl;
    
    aud.load(path);
}

//--------------------------------------------------------------
void ofApp::audToggle(){
    
//    if(aud.isPlaying()){
//        aud.setPaused(true);
//    } else {
//        if(aud.getPosition() == 0.0){
//            aud.play();
//        } else {
//            aud.setPaused(false);
//        }
//    }
    
    aud.play();
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case 'h':
        {
            gui1->toggleVisible();
        }
            break;
    }
    
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
    
    for(int i=0; i<9; i++){
        if( (x>=cells[i].pos.x && x<=cells[i].pos.x+cells[i].size.x) && (y>=cells[i].pos.y && y<=cells[i].pos.y+cells[i].size.y) ){
            
            cells[i].state = !cells[i].state;
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
