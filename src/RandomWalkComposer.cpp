//
//  RandomWalkComposer.cpp
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 09/07/14.
//
//

#include "RandomWalkComposer.h"
#include "Randomize.h"
#include "Note.h"
#include "Utils.h"
#include "Scales.h"
#include "App.h"
#include <sstream>

RandomWalkComposer::RandomWalkComposer(){

	octave = -1;

    type = RandomWalk;
    boundary = Reflecting;
	startingGrade = 0;

	maxOctave = 4;
	minOctave = 2;

	scale = 0;
	figureType = patternType;

	minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
	maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);

}

void RandomWalkComposer::setMaxOctave(int m){
	maxOctave = m + 1;
	maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);
}

void RandomWalkComposer::setMinOctave(int m){
	minOctave = m;
	minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
}

RandomWalkComposer::~RandomWalkComposer(){


}

void RandomWalkComposer::setPitchesBasedOnScaleAndOctaves(){

	int max = 7;
	if (scale == 0)
		max = 12;
	else if (scale == 1)
		max = 5;

	pitches.clear();

	for (int octave = minOctave; octave <= maxOctave; octave++) {

		for (int tone = 0; tone < max; tone++) {
			int pitch = 10*(octave + 2) + ListOfScales[scale][tone] + (2*octave + 4);
			pitches.push_back(pitch);
		}

	}

}

vector<Figure *> RandomWalkComposer::compose(bool infinite){

    //cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<endl;
	//cout << "min octave: " << minOctave << " min pitch: " << minPitch << endl;
	//cout << "max octave: " << maxOctave << " max pitch: " << maxPitch << endl;

	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	float duration;
	bool firstDone = false;

	int currentPitch;

	int prevRelativePitch;

	if(octave == -1)
		octave = Utils::map(Randomize::getRandomValue(), 0, 1, minOctave, maxOctave);
	int octaveChangeDown = OctaveDown[scale];
	int octaveChangeUp = OctaveUp[scale];

	if(Figure::typeToDuration(figureType) > Figure::typeToDuration(patternType))
		figureType = patternType;

	setPitchesBasedOnScaleAndOctaves();
	int currentPosition = pitches.size() / 2;

	for (int i = 0; i < stems; i++) {
		while (counter < total) {
			if (firstDone) {
				direction = Randomize::getRandomDirection();

				if (direction) {
					currentPosition++;
				}
				else{
					currentPosition--;
				}

				if (boundary == Reflecting) {
					if (currentPosition == pitches.size()) {
						currentPosition -= 2;
					}
					if (currentPosition == -1) {
						currentPosition = 1;
					}
				}
				else if (boundary == Absorbing){
					if (currentPosition == pitches.size()) {
						currentPosition -= 1;
					}
					if (currentPosition == -1) {
						currentPosition = 0;
					}
				}

			}

			else{
				firstDone = true;
			}
			counter += Figure::typeToDuration(figureType);

			Note * note = new Note(figureType, pitches[currentPosition], 50);
			fragment.push_back(note);
		}
		counter = 0;
	}

	/*int scaleLimit = 7;
	if (scale == 0) {
		scaleLimit = 12;
	}
	else if (scale == 1){
		scaleLimit = 5;
	}

	//int currentRelativePitch = Utils::map(Randomize::getRandomValue(), 0, 1, 0, scaleLimit);
	int currentRelativePitch = startingGrade;

	cout << "empieza en " << currentRelativePitch <<", octava " << octave << endl;

	for(int i = 0; i < stems; i++){

		while(counter < total){

			if(firstDone){
				prevRelativePitch = currentRelativePitch;
				direction = Randomize::getRandomDirection();

				if (direction) {
					cout << "arriba" << endl;

					currentRelativePitch++;

					cout<<currentRelativePitch<<endl;

					if (currentRelativePitch == scaleLimit){
						cout<<"vuelta +"<<endl;
						currentRelativePitch = 0;
						cout<<currentRelativePitch<<endl;
					}
					if (currentRelativePitch == octaveChangeUp) {
						cout<<"cambio octava"<<endl;
						octave++;
						cout<<currentRelativePitch<<", octava: "<<octave<<endl;

					}

					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
					cout << currentPitch << endl;


					if (currentPitch > maxPitch) {
						cout << "Se pasa por arriba" << endl;
						currentRelativePitch = scaleLimit - 1;
						octave = maxOctave - 1;
						currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
					}

					cout << currentPitch << endl;
				}
				else if (!direction){
					cout << "abajo" << endl;

					currentRelativePitch--;

					cout << currentRelativePitch << endl;

					if (currentRelativePitch == -1) {
						cout<<"vuelta -"<<endl;
						currentRelativePitch = scaleLimit - 1;
						cout<<currentRelativePitch<<endl;
					}
					if (currentRelativePitch == octaveChangeDown) {
						cout<<"cambio octava"<<endl;
						octave--;
						cout<<currentRelativePitch<<", octava: "<<octave<<endl;
					}

					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
					cout << currentPitch << endl;

					if (currentPitch < minPitch) {
						cout << "se pasa por abajo" << endl;
						currentRelativePitch = 1;
						octave = minOctave;
						currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
					}

					cout << currentPitch << endl;
				}

				counter += Figure::typeToDuration(figureType);

				Note * note = new Note(figureType, currentPitch, 50);
				fragment.push_back(note);
				cout << "octava " << octave << ", relative pitch " << currentRelativePitch << " pitch " << currentPitch << endl;
				cout << "---" << endl;
			}
			else{
				currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
				firstDone = true;

				counter += Figure::typeToDuration(figureType);

				Note * note = new Note(figureType, currentPitch, 50);
				fragment.push_back(note);
				cout << "octava " << octave << ", relative pitch " << currentRelativePitch << " pitch " << currentPitch << endl;
				cout << "---" << endl;
			}

		}

		counter = 0.0;
	}
	*/


	stringstream sst;
	sst << "Got " << fragment.size() << " figures ";
	App::addLogMessage(sst.str());

	return fragment;

}
