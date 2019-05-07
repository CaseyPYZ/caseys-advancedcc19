#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // check if data file already exists
    string fileName = ofToDataPath(FILE_PATH);
    fin.open(fileName.c_str(), ios::in);
    if(fin.is_open()){
        data_ready = true;
        data_saved = true;
    }
    fin.close();

    
    // read data
    
    if(data_ready){
        
        /*
         Read data from local XML file
         */
        
        ofLogNotice("data_src") << "Data read from XML file." << endl;
        
        if ( xml.loadFile(FILE_PATH) ){
            xml.pushTag("incidts");
            fsize = xml.getNumTags("incidt");
            
            for(int k=0; k<fsize; k++){
                xml.pushTag("incidt", k);
                
                string tstamp = xml.getValue("timestamp", "0");
                string tvals = xml.getValue("timeval", "0");
                int xp = xml.getValue("x_pos",0);
                int yp = xml.getValue("y_pos",0);
                auto incdt = make_shared<Incident>(tstamp, tvals, xp, yp);
                
                incidents.push_back(incdt);
                xml.popTag();
            }
            xml.popTag();
            
        } else {
            ofLogError("Incidents data file did not load.");
        }
        
    } else {
        
        /*
         Read raw data from NYC Open Data json api
         */
        
        ofLogNotice("data_src") << "Data read from URL." << endl;
        
        //std::string url = "https://data.cityofnewyork.us/resource/833y-fsy8.json?$limit=20000&$$app_token=gkNekzywG9Gf1HHElNzW9qaxc";
        
        
        // Now parse the JSON
        bool parsingSuccessful = json.open(url);
        
        if (parsingSuccessful)
        {
            ofLogNotice("ofApp::setup") << json.getRawString(true);
        } else {
            ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
        }
        
        
        /*
         Process json data
         Instantiate a Incident object off of each data unit
         */
        
        for (Json::ArrayIndex i = 0; i < json.size(); ++i)
        {
            string date  = json[i]["occur_date"].asString();
            string time = json[i]["occur_time"].asString();;
            string x_str = json[i]["x_coord_cd"].asString();
            string y_str = json[i]["y_coord_cd"].asString();
            
            
            // date
            
            string yr = date.substr(0,4);
            string mth = date.substr(5,2);
            string day = date.substr(8,2);
            
            string datetxt = yr + mth + day;
            
            // time
            
            int p1 = time.find(del);
            int p2 = time.substr( p1+1, time.size()-p1-1 ).find(del);
            
            string h = time.substr(0,p1);
            string m = time.substr(p1+1,p2);
            //string s = time.substr(p1+p2+2,2);
            
            if(h.size()==1){
                h = "0" + h;
            }
            
            string timetxt = h + m;
            
            string ftxt = datetxt + timetxt;
            
            // create a pointer of a new Incient & push_back to Incident vector
            auto incdt = make_shared<Incident>(ftxt, x_str, y_str);
            incidents.push_back(incdt);
            
        }
        
        
        /*
         Sort incidents vector in chronological order
         according to the Incidents' "timeval" property (unsigned int)
         */
        
        //std::sort(incidents.begin(), incidents.end());
        
        //sort(incidents.begin(), incidents.end(), incdtObject);
        //std::sort(incidents.begin(), incidents.end(), &ofApp::comparIncdt);
        
        //ofSort(incidents);
        
    }
    
    clkfont.load("font/plantagenet-cherokee.ttf", 12);
    
    canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // clock++ (if not paused)
    if(!paused){
        clockPlus();
    }
    
    for(int i=0; i<incidents.size(); i++){
        if(incidents[i]->timeval<=clock){
            incidents[i]->happened = true;
        } else {
            incidents[i]->happened = false;
        }
    }
    
    if(clock<1000000000){
        clkpre = "200";
    } else {
        clkpre = "20";
    }
    
    clkstr = clkpre + to_string(clock).substr(0,1+pos_offset) + "-" + to_string(clock).substr(1+pos_offset,2) + "-" + to_string(clock).substr(3+pos_offset,2);
    //clkstr_b = to_string(clock).substr(5+pos_offset,2) + ":00";
    

}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    canvas.begin();
    
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(200);
    for(int i=0; i<incidents.size(); i++){
        
        if(incidents[i]->happened){
            incidents[i]->display();
        }
    }
    canvas.end();
    
    canvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if(showstr){
        clkfont.drawString(clkstr, 30, 30);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    ofLogNotice("data_saved") << data_saved << endl;
    
    /*
     If "shooting_data.xml" doesn't exist yet
     Save Incidents vector data to local XML file
    */
    
    if(!data_saved){
        
        xml.addTag("incidts");
        xml.pushTag("incidts");
        
        for(int i=0; i<incidents.size(); i++){
            
            xml.addTag("incidt");
            xml.pushTag("incidt", i);
            xml.addValue("timestamp", incidents[i]->timestamp);
            xml.addValue("timeval", to_string(incidents[i]->timeval));
            xml.addValue("x_pos", incidents[i]->x_pos);
            xml.addValue("y_pos", incidents[i]->y_pos);
            
            xml.popTag();
        }
        
        xml.popTag();
        xml.saveFile(FILE_PATH);
        
        data_saved = true;
        
        ofLogNotice("on exit") << "Data saved" << endl;
        
    }
    
}

//--------------------------------------------------------------
bool ofApp::comparIncdt(shared_ptr<Incident> lhs, shared_ptr<Incident> rhs){
    return (lhs->timeval < rhs->timeval);
}

//--------------------------------------------------------------
void ofApp::clockPlus(){
    
    // + 1h
    clock+=100;
    
    // constrain clock value
    if(clock<=CLOCK_INIT){
        clock=CLOCK_INIT;
    } else if (clock>=CLOCK_MAX){
        clock=CLOCK_MAX;
    }
    
    // 9 -> 10 digits
    if( clock>=1000000000 ){
        pos_offset = 1;
    } else {
        pos_offset = 0;
    }
    
    // 24h -> 1d
    
    if( to_string(clock).substr(5+pos_offset,2).compare("24")==0 ){
        clock+=7600; // clock-=2400;clock+=10000;
    }
    
    // 30d -> 1m
    
    if( to_string(clock).substr(3+pos_offset,2).compare(full_month)==0 ){
        clock+=700000; // clock-=300000;clock+=1000000;
    }
    
    // 12m -> 1y
    
    if( to_string(clock).substr(1+pos_offset,2).compare("13")==0 ){
        clock+=87000000; // clock-=13000000;clock+=100000000;
    }
    
    // full month - 30/31
    
    int month = stoi(to_string(clock).substr(1+pos_offset,2));
    if( month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
        full_month = "31";
    } else {
        full_month = "30";
    }
    
    
}

//--------------------------------------------------------------
void ofApp::exportPDF(){
    
    grabbedImg.grabScreen(0,0,ofGetWidth(), ofGetHeight());

    tex = canvas.getTexture();
    tex.readToPixels(pix);
    
    for(int i=0; i<pix.size(); i++){
       pix[i] = 255 - pix[i];
    }
    
    colorImg.setFromPixels(pix);
    greyImg = colorImg;
    
    ctrFinder.findContours(greyImg, 1, 300, 19000, false, true);
    
    ofBeginSaveScreenAsPDF("vecSnapshot-"+clkstr+".pdf");
    ctrFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofEndSaveScreenAsPDF();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 's' ){
        ss.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        ss.save("snapshot-"+clkstr+".png");
    } else if ( key == 'x'){
        exportPDF();
    } else if ( key == ' '){
        paused = !paused;
    } else if ( key == 't'){
        showstr = !showstr;
    } else if ( key == OF_KEY_UP){ // +1y
        clock+=100000000;
    } else if ( key == OF_KEY_DOWN){
        clock-=100000000;
    } else if ( key == OF_KEY_RETURN){
        clock = CLOCK_INIT;
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
