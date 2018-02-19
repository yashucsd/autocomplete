#include "util.h"
#include "DictionaryHashtable.h"

/* 	Dictionary in form of hash table
    Yash Nevatia & Josh Hunter
    20 April 2017
*/

using namespace std;

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
	data = new unordered_set<string>();
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
	if(word.empty()) return false;
	return (data->insert(word)).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
	if(word.empty()) return false;
	return data->find(word) != data->end();
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
	delete(data);
}