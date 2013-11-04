#include "testApp.h"

#include "ofxSPK.h"

ofxSPK::System sys;
ofxSPK::Group group;

ofImage sprite;

ofxSPK::Modifier rot;

//--------------------------------------------------------------
void testApp::setup(){
    
    /**** SPK setup *****/
    // setup pointsprite texture
	// NOTES: the texture size must be Power of Two,
	// and turn off arb texture option while loading
	ofDisableArbTex();
	sprite.loadImage("particle32.png");
	ofEnableArbTex();
	
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	sys.setup();
	
	group.setup(sys);
	group.setColor(ofxSPK::RangeC(ofColor(255, 255), ofColor(255, 255)),
				   ofxSPK::RangeC(ofColor(0, 0), ofColor(255, 0)));
	
	group.setLifeTime(0.5, 5);
	group.setFriction(0.1);
	group.setSize(0, ofxSPK::RangeF(30, 250));
	
	group.setGravity(ofVec3f(0, 0, 0));
	group.setMass(0.1, 1);
	
	rot.setup(SPK::Vortex::create(SPK::Vector3D(ofGetWidth()/2, ofGetHeight()/2),
								  SPK::Vector3D(0, 1, 0),
								  200,
								  10), group);
	
	group.reserve(1000);
    
    
    /******** LeapMotion setup *********/
    // 照明とカメラ
    /*ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();*/
    cam.setOrientation(ofPoint(20, 0, 0));
    // GL設定
    //glEnable(GL_DEPTH_TEST);
    
    // Leap Motion開始
    leap.open();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    /*** SPK update ***/
    /*
    group.emitRandom(10, ofVec3f(ofGetMouseX(), ofGetMouseY()));
	sys.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
    */
    
    //printf("%d\n", ofGetMouseX());
    
    
    
    
    /*** LeapMotion update ***/
    // Leap Motion SDKで用意されている手(Hand)のクラスを取得してvector配列へ
    vector <Hand> hands = leap.getLeapHands();
    
    // 手が検出されたら
    if( leap.isFrameNew() && hands.size() ){
        // vector配列に記憶した座標をクリア
        fingerPos.clear();
        spherePos.clear();
        sphereSize.clear();
        
        // 画面の大きさにあわせて、スケールをマッピング
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        for(int i = 0; i < hands.size(); i++){
            // 指の位置を取得
            for(int j = 0; j < hands[i].fingers().count(); j++){
                ofVec3f pt;
                const Finger & finger = hands[i].fingers()[j];
                pt = leap.getMappedofPoint( finger.tipPosition() );
                fingerPos.push_back(pt);
            }
            
            // 指がとりかこむ球体を取得
            ofVec3f sp = leap.getMappedofPoint(hands[i].sphereCenter());
            float r = hands[i].sphereRadius();
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            
            
            // SPKに渡す座標を調整
            ofVec3f spkcoord;
            spkcoord.x = sp.x + (ofGetWidth() / 2);
            spkcoord.y = ( (sp.y + 100) * 0.8);
            spkcoord.z = sp.z;
            
            group.emitRandom(10, spkcoord);
            sys.update();
            ofSetWindowTitle(ofToString(ofGetFrameRate()));
        }
    }
    
    // ofxLeapMotionに現在のフレームは古くなったことを通知
    leap.markFrameAsOld();
}

//--------------------------------------------------------------
void testApp::draw(){

    /*** SPK Draw ***/
    ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// sys.debugDraw();
	
	// bind texture, enable point sprite while drawing particles
	sprite.bind();
	ofEnablePointSprites();
	sys.draw();
	ofDisablePointSprites();
	sprite.unbind();
    
    
    
    
    /*** leap draw ***/
    /*
    cam.begin();
    // 検出された指の数だけくりかえし
    for(int i = 0; i < fingerPos.size(); i++){
        // 検出された位置に球を描画
        ofSpherePrimitive sphere;
        sphere.setPosition(fingerPos[i].x, fingerPos[i].y, fingerPos[i].z);
        sphere.draw();
    }
    
    // 検出された指がとりかこむ球
    for(int i = 0; i < spherePos.size(); i++){
        // 検出された位置に球を描画
        ofSpherePrimitive sphere;
        sphere.setPosition(spherePos[i].x, spherePos[i].y, spherePos[i].z);
        sphere.setRadius(sphereSize[i]*1.5); //ここのスケールは今は目分量…
        sphere.draw();
    }
    cam.end();
    */
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
