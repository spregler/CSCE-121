#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "functions.h"
#include "provided.h"

using namespace std;

int main () {

	int ngames;
	int duration;
	string fname;
	ifstream fin;

	string myPath = "C:/Users/seth/OneDrive/Documents/CSCE/hw5/";
	string titles_filename;
	string pref_filename;
	string plan_filename;

	int plan[366];
	int prefs[MAX_NB_GAMES]; // preferences array of size MAX_NB_GAMES
	string gameTitles[MAX_NB_GAMES]; // game titles array of size MAX_NB_GAMES


	cout << "Please enter the number of games and the duration: ";
	cin >> ngames; //read in number of games from user
	cin >> duration; //read in duration from user
	// throw invalid input if 0 < ngames <= 200
	if (!((ngames > 0 ) && (ngames <= 200))) {
		cout << "Invalid input." << endl;
		return 0;
	}
	if ((duration < 0)) {
		cout << "Invalid input." << endl;
		return 0;
	}

	// TITLES //
	cout << "Please enter name of file with titles: ";
	cin >> titles_filename; //concatinate fname with the path
	// PREFERENCES //
	cout << "Please enter name of file with preferences: ";
	cin >> pref_filename; // read in file with preferences
	 
	// PLAN //
	cout << "Please enter name of file with plan: ";
	cin >> plan_filename ;
		


	fin.open(titles_filename);
	if (!fin.is_open()) {
		cout << "Invalid titles file.";
		return 0;
	}
	fin.close();

	fin.open(pref_filename);
	if (!fin.is_open()) {
		cout << "Invalid preference file.";
		return 0;
	}
	fin.close();

	fin.open(plan_filename);   
	if (!fin.is_open()) {
		cout << "Invalid plan file.";
		return 0;
	}
	fin.close();

	readGameTitles(titles_filename, ngames, gameTitles);
	readPrefs(pref_filename, ngames, prefs);
	readPlan(plan_filename, plan);

	int bestDay = findBestVacation(duration, prefs, plan);
	cout << "Best start day is " << bestDay << endl;
	cout << "Games to be played:"  << endl;
	printGamesPlayedInVacation(bestDay, duration, plan, gameTitles, ngames);

}
