#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // check if data file already exists
    string fileName = ofToDataPath(file_path);
    fin.open(fileName.c_str(), ios::in);
    if(fin.is_open()){
        data_ready = true;
    }
    fin.close();

    
    // read data
    if(data_ready){
        
        ofLogNotice("data_src") << "Data read from XML file." << endl;
        
        if ( xml.loadFile(file_path) ){
            xml.pushTag("incidts");
            fsize = xml.getNumTags("incidt");
            
            for(int k=0; k<fsize; k++){
                xml.pushTag("incidt", k);
                
                string tstamp = xml.getValue("timestamp", "0");
                string xs = xml.getValue("x_str", "0");
                string ys = xml.getValue("y_str", "0");
                auto incdt = make_shared<Incident>(tstamp, xs, ys);
                
                incidents.push_back(incdt);
                xml.popTag();
            }
            xml.popTag();
            
        } else {
            ofLogError("Incidents data file did not load.");
        }
        
        
    } else {
        // read data from NYC Open Data json api
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
         Save data to xml
         */
        
        xml.addTag("incidts");
        xml.pushTag("incidts");
        
        for (Json::ArrayIndex i = 0; i < json.size(); ++i)
        {
            string date  = json[i]["occur_date"].asString();
            string time = json[i]["occur_time"].asString();
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
            string s = time.substr(p1+p2+2,2);
            
            if(h.size()==1){
                h = "0" + h;
            }
            
            string timetxt = h + m + s;
            
            string ftxt = datetxt + timetxt;
            
            // create a pointer of a new Incient & push_back to Incident vector
            auto incdt = make_shared<Incident>(ftxt, x_str, y_str);
            incidents.push_back(incdt);
            
            xml.addTag("incidt");
            xml.pushTag("incidt", i);
            xml.addValue("timestamp", ftxt);
            xml.addValue("x_str", x_str);
            xml.addValue("y_str", y_str);
            xml.popTag();
            
        }
        
        xml.popTag();
        xml.saveFile(file_path);
        
    }
    
    


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);
    
    ofDrawBitmapString("Incidents num: " + to_string(incidents.size()), 20, 20);
    
    for(int i=0; i<20; i++){
        auto incd = incidents[i];
        ofDrawBitmapString(incd->timestr, 20, i*20+40);
    }
    

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
