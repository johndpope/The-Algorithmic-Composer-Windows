#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Composer.h"
#include "Player.h"

#include "UniformDistribution.h"
#include "LinearDistribution.h"
#include "TriangularDistribution.h"
#include "ExponentialDistribution.h"
#include "GaussianDistribution.h"
#include "CauchyDistribution.h"
#include "BetaDistribution.h"
#include "WeibullDistribution.h"
#include "PoissonDistribution.h"
#include "MusicVisualizer.h"

#include <iostream>
using namespace std;


class App : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);



	static float getFramerate(){ return ofGetFrameRate(); }

	static void setMidiNote(int note);
	static void setIsSilence(bool t);
	static void setVolume(float volume);
	static void setCurrentFigure(Figure * f);

	static int getTempo(){ return player->getTempo(); }
	static ofColor getUIColor();
	static Composer * getComposer(){ return composer; }
	static MusicVisualizer * getMusicVisualizer(){ return mv; }

	static void addLogMessage(string s);

	static std::vector<Figure *> composition;


private:

	static bool infinite;

	static Composer * composer;
	static Player * player;
	static MusicVisualizer * mv;

	void initSynth();
	void initGUI();
	void setValuesForGraph(Distribution * d);

	void showIndependentStochasticGUI(bool show);
	void showMarkovChainsGUI(bool show);
	void showRandomWalkGUI(bool show);
	void showMotivicDevelopmentGUI(bool show);
	void showSerialGUI(bool show);
	void showFractionalNoiseGUI(bool show);
	void showChaoticResponseGUI(bool show);

	void setGUITheme(int i);
	void toggleDistribution();
	void drawGrid(float x, float y);


	UniformDistribution * uniform;
	LinearDistribution * linear;
	TriangularDistribution * triangular;
	ExponentialDistribution * exponential;
	GaussianDistribution * gauss;
	CauchyDistribution * cauchy;
	BetaDistribution * beta;
	WeibullDistribution * weibull;
	PoissonDistribution * poisson;

	void guiEvent(ofxUIEventArgs &e);

	vector<ofxUICanvas *> guis;
	ofxUICanvas * methodGUI;
	static ofxUIScrollableCanvas * resultsGui;
	ofxUICanvas * generalGUI;
	ofxUICanvas * styleGUI;
	ofColor backgroundColor;
	float red, green, blue;
	ofTrueTypeFont musicNotesFont;

	static ofxUITextArea *currentFigureLabel;
	ofxUIRadio *scaleRadioButtons;
	ofxUIImageToggle * pauseToggle;
	ofxUICanvas * optionsGUI;
	static ofxUIScrollableCanvas * logGUI;
	int initialY;


	/* INDEPENDENT STOCHASTIC GUI */

	ofxUICanvas *isGUI1;
	ofxUIScrollableCanvas *isGUI2;
	ofxUICanvas *isGUI3;

	ofxUICanvas *distributionListGUI;

	ofxUIMovingGraph * mg;
	ofxUICanvas * distributionGUI;
	ofxUICanvas * linearDistGUI;
	ofxUICanvas * triangularDistGUI;
	ofxUICanvas * exponentialDistGUI;
	ofxUICanvas * gaussDistGUI;
	ofxUICanvas * cauchyDistGUI;
	ofxUICanvas * betaDistGUI;
	ofxUICanvas * weibullDistGUI;
	ofxUICanvas * poissonDistGUI;
	ofxUICanvas * fixedGUI;

	ofxUIMovingGraph * mg2;
	ofxUICanvas * distributionGUI2;
	ofxUICanvas * linearDistGUI2;
	ofxUICanvas * triangularDistGUI2;
	ofxUICanvas * exponentialDistGUI2;
	ofxUICanvas * gaussDistGUI2;
	ofxUICanvas * cauchyDistGUI2;
	ofxUICanvas * betaDistGUI2;
	ofxUICanvas * weibullDistGUI2;
	ofxUICanvas * poissonDistGUI2;
	ofxUICanvas * fixedGUI2;

	ofxUIMovingGraph * mg3;
	ofxUICanvas * distributionGUI3;
	ofxUICanvas * linearDistGUI3;
	ofxUICanvas * triangularDistGUI3;
	ofxUICanvas * exponentialDistGUI3;
	ofxUICanvas * gaussDistGUI3;
	ofxUICanvas * cauchyDistGUI3;
	ofxUICanvas * betaDistGUI3;
	ofxUICanvas * weibullDistGUI3;
	ofxUICanvas * poissonDistGUI3;
	ofxUICanvas * fixedGUI3;

	ofxUICanvas * isHelpGUI;

	int selectedDistribution;

	/* MARKOV CHAINS GUI */

	ofxUICanvas *mcGUI1;
	ofxUICanvas *mcGUI2;
	ofxUISlider * mcPitchesSlider;
	ofxUIRadio * mcDurationsRadio;
	ofxUILabel *fileLabel;
	ofxUICanvas * mcHelpGUI;

	/* RANDOM WALK GUI */

	ofxUICanvas *rwGUI;
	ofxUICanvas * rwHelpGUI;

	/* MOTIVIC DEVELOPMENT GUI */

	ofxUIScrollableCanvas *mdGUI0;
	ofxUICanvas *mdGUI1;
	ofxUICanvas *mdGUI2;
	ofxUICanvas *mdGUI3;
	ofxUISortableList *sortableList;
	vector<ofxUILabel *> labels;
	ofxUICanvas * mdHelpGUI;

	/* SERIAL GUI */

	ofxUICanvas *sGUI0;
	ofxUICanvas *sGUI1;
	ofxUICanvas *sGUI2;
	ofxUICanvas *sGUI3;
	ofxUITextArea * melodicListLabel;
	ofxUITextArea * rhythmicListLabel;
	ofxUITextArea * seriesListLabel;
	vector<string> melodicList;
	vector<string> rhythmicList;
	vector<string> seriesList;
	vector<ofxUILabel *> sequenceListLabels;

	ofxUICanvas * sHelpGUI;


	/* FRACTIONAL NOISE GUI */


	ofxUICanvas *fsGUI0;
	ofxUICanvas *fsGUI1;
	ofxUIScrollableCanvas *fsGUI2;
	ofxUISlider * fsPitchesSlider;
	ofxUIRadio * fsDurationsRadio;

	ofxUICanvas * fsHelpGUI;

	/* CHAOTIC RESPONSE GUI */

	ofxUICanvas *crGUI0;
	ofxUICanvas *crGUI1;
	ofxUICanvas *crGUI3;
	ofxUIScrollableCanvas *crGUI2;
	ofxUICanvas *crLogisticGUI;
	ofxUICanvas *crHenonGUI;
	ofxUICanvas *crMandelbrotGUI;
	ofxUICanvas *crTentMapGUI;

	ofxUICanvas * crHelpGUI;

};
