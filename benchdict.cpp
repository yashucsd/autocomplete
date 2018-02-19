#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

#define LETTERS 26
#define NUMWORDS 100
#define IMPOSSIBLEFIND 10
#define NUMARGS 5
#define NUMDIGITS 3

/*  main for benchdict benchmarking different data structures.
    Yash Nevatia & Josh Hunter
    20 April 2017
*/

using namespace std;

int main(int argc, char** argv) {

    int j = 0;

    //Check number of arguments
	if(argc != NUMARGS){
		cout << "Wrong number of arguments" << endl;
		return -1;
	}

    //Validate digits.
    for(int i = 1; i <= NUMDIGITS; i++) {
        j = 0;

        while(argv[i][j] != '\0') {
            if(!isdigit(argv[i][j])) {
                cout << "Argument is not a number" << endl;
                return -1;
            }
            j++;
        }
    }

	int min_size = stoi(argv[1]);
	int step_size = stoi(argv[2]);
	int num_iterations = stoi(argv[3]);
	string dictfile = "../";
	dictfile.append(argv[4]);
	vector<string> words;
	ifstream file(dictfile);

	if(!file.good()){ // checks if file exists
		cout << "File not found" << endl;
		return -1;
	}
	file.close();

	DictionaryBST * bst;

	cout << "Benching BST..." << endl;

	for (int i = 0; i < num_iterations; ++i){
		bst =  new DictionaryBST();
		words.erase(words.begin(), words.end());

		int dict_size = min_size + i * step_size;

		file.open(dictfile); // loads dictionary
		Utils::load_dict(*bst, file, dict_size);
		Utils::load_vector(words, file, NUMWORDS);
		file.close();

		long long totalRunTimes = 0;

		Timer timer;

		for(int j = 0; j < IMPOSSIBLEFIND; j++){
			timer.begin_timer(); // times the finding of words
			for(string word : words)
				bst->find(word);
			totalRunTimes += timer.end_timer();
		}

		long long averageRunTime = totalRunTimes / IMPOSSIBLEFIND;

		cout << dict_size << "\t" << averageRunTime << endl;

	}

	delete bst;

	DictionaryHashtable * ht;

	cout << "Benching HT..." << endl;

	for (int i = 0; i < num_iterations; ++i){
		ht = new DictionaryHashtable();
		words.erase(words.begin(), words.end());

		int dict_size = min_size + i * step_size;


		file.open (dictfile);
		Utils::load_dict(* ht, file, dict_size);
		Utils::load_vector(words, file, NUMWORDS);
		file.close();

		long long totalRunTimes = 0;

		Timer timer;

		for(int j = 0; j < IMPOSSIBLEFIND; j++){
			timer.begin_timer();
			for(string word : words)
				ht->find(word);
			totalRunTimes += timer.end_timer();
		}

		long long averageRunTime = totalRunTimes / IMPOSSIBLEFIND;

		cout << dict_size << "\t" << averageRunTime << endl;

	}

	delete ht;

	DictionaryTrie * mvt;
	
	cout << "Benching MVT..." << endl;

	for (int i = 0; i < num_iterations; ++i){
		mvt = new DictionaryTrie();
		words.erase(words.begin(), words.end());

		int dict_size = min_size + i * step_size;

		file.open (dictfile);
		Utils::load_dict(*mvt, file, dict_size);
		Utils::load_vector(words, file, NUMWORDS);
		file.close();

		long long totalRunTimes = 0;

		Timer timer;

		for(int j = 0; j < IMPOSSIBLEFIND; j++){
			timer.begin_timer();
			for(string word : words)
				mvt->find(word);
			totalRunTimes += timer.end_timer();
		}

		long long averageRunTime = totalRunTimes / IMPOSSIBLEFIND;

		cout << dict_size << "\t" << averageRunTime << endl;
	}

	delete mvt;
}
