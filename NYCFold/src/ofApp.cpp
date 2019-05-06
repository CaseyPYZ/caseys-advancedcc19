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
        
        std::sort(incidents.begin(), incidents.end()); //- use overloaded operator< ?
        //sort(incidents.begin(), incidents.end(), incdtObject);
        //std::sort(incidents.begin(), incidents.end(), &ofApp::comparIncdt);
        
    }
    


}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    ofSetColor(180);
    ofDrawBitmapString("Incidents num: " + to_string(incidents.size()), 20, 20);
    
    for(int i=0; i<incidents.size(); i++){
        auto incd = incidents[i];
        //ofDrawBitmapString(to_string(i)+" - "+incd->timestamp+" - "+to_string(incd->timeval)+" ["+to_string(incd->x_coord)+","+to_string(incd->y_coord)+"] - ["+to_string(incd->x_pos)+","+to_string(incd->y_pos)+"]" , 20, i*20+60);
        
        incd->display();
        //ofLog() << i << endl;
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
void ofApp::keyPressed(int key){
    
    if( key=='s' ){
        ss.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        ss.save("screenshot.png");
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
