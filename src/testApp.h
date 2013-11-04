#pragma once

#include "ofMain.h"
#include "ofxLeapMotion.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        /* LeapMotion SetUp */
        ofxLeapMotion leap; // Leap Motionのメインクラスをインスタンス化
        // vector <ofxLeapMotionSimpleHand> simpleHands; // シンプルな手のモデルのvector配列
        ofEasyCam cam; //カメラ
        ofLight light; //ライト
        vector <ofVec3f> fingerPos; // 指の位置の配列
        vector <ofVec3f> spherePos; // 手が取り囲む球体の位置の配列
        vector <float> sphereSize;  // 手が取り囲む球体の大きさの配列
    
};
