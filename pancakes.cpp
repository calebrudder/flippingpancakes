// flipping pancakes
// Caleb Rudder
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

void BFS(string, int&);
string flipSubString(string, int);

void main() {
	ifstream fin("pancakes.in");
	if (fin.is_open()) {
		ofstream fout("pancakes.out");

		string input;
		int flipCount = 0;
		fin >> input;

		while (input != "0") {
			BFS(input, flipCount);
			fout << flipCount << endl;
			fin >> input;
		}


		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}

struct Pancake {
	string input = "";
	int flipCount = 0;
	bool visited = 0;
};

void BFS(string input, int &flipCount) {

	string finalGoal = input;
	Pancake currentPancake;
	set<string> uniquePancakeCombos;
	queue<Pancake> pancakes;

	for (int i = 0; i <= finalGoal.length() -1; i++) {

		if (finalGoal[i] > 96 && finalGoal[i] < 122) {
			finalGoal[i] = toupper(finalGoal[i]);
		}
		sort(finalGoal.begin(), finalGoal.end());
	}

	currentPancake.input = input;
	uniquePancakeCombos.insert(input);
	pancakes.push(currentPancake);

	while (!pancakes.empty()) {

		Pancake poppedPancake = pancakes.front();
		pancakes.pop();

		if (poppedPancake.input == finalGoal) {
			flipCount = poppedPancake.flipCount;
			while (!pancakes.empty()) {
				pancakes.pop();
			}
		}
		else {

			for (int i = 0; i < currentPancake.input.size(); i++) {
			
				Pancake newCake;
				newCake.input = flipSubString(poppedPancake.input, i);
				newCake.flipCount = poppedPancake.flipCount;
				newCake.flipCount++;
				bool has = uniquePancakeCombos.find(newCake.input) != uniquePancakeCombos.end();
				if (!has) {
					pancakes.push(newCake);
				}
				uniquePancakeCombos.insert(newCake.input);

			}

		}

	}
	



}

string flipSubString(string s, int pos) {
	string result = s;
	int toPos = pos;

	for (int i = s.length() - 1; i >= pos; i--) {
		if (s[i] > 96 && s[i] < 122) {
			result[toPos] = toupper(s[i]);
			toPos++;
		}
		else {
			result[toPos] = tolower(s[i]);
			toPos++;
		}
	}
	return result;
}