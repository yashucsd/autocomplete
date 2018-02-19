#include "util.h"
#include "DictionaryBST.h"

/* 	Dictionary in form of Binary Search tree
    Yash Nevatia & Josh Hunter
    20 April 2017
*/


/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
    BSTData = new set<string>;
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    if(word == "") return false;
    return BSTData->insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
    return BSTData->find(word) != BSTData->end();
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
    BSTData->clear();
    delete( BSTData );
}
