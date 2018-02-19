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
using namespace std;

/* 	tests for three dictionary implementiations
    Yash Nevatia & Josh Hunter
    20 April 2017
*/

int main(int argc, char** argv) {
    std::vector<string> strings;
    int i =0;
  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("this has spaces");

  cout << "Searching for items not in yet." << endl;
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }
  
  cout << endl << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }
 
  cout << endl << "Finding elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  nope = {""};
  nit = nope.begin();

  cout << "Inserting:  null... ";
  t_bst = d_bst.insert(*nit);
  t_ht = d_ht.insert(*nit);
  tt = dt.insert(*nit, 1);
  if(t_bst)
    {
      cout << "failed for DictionaryBST... ";
    }
  if(t_ht)
    {
      cout << "failed for DictionaryHashset... ";
    }
  if(tt)
    {
      cout << "failed for DictionaryTrie... ";
    }
  if(!t_bst && !t_ht && !tt)
    {
      cout << "PASSED! :D ";
    }
  cout << endl;

	DictionaryBST loaded_bst;
	DictionaryHashtable loaded_ht;
	DictionaryTrie loaded_t;

	ifstream file;

 	cout << endl << "Loading into dictionaries...";

 	file.open ("../freq3.txt");
	Utils::load_dict(loaded_bst, file);
	file.close();

	file.open ("../freq3.txt");
	Utils::load_dict(loaded_ht, file);
	file.close();
	
	file.open ("../freq3.txt");
	Utils::load_dict(loaded_t, file);
	file.close();

	cout << "looks good !" << endl;

	vector<std::string> loadedWords;
	vector<string>::iterator lwit;
	vector<string>::iterator lwen;

	loadedWords.push_back("aa");
	loadedWords.push_back("a balky");
	loadedWords.push_back("already there");
	loadedWords.push_back("zz top");
	loadedWords.push_back("euphemize");

	cout << endl << "Finding elements that were just loaded into Dictionaries..." << endl;

	lwit = loadedWords.begin();
	lwen = loadedWords.end();
	for(; lwit != lwen; ++lwit) {
	    cout << "Finding: \"" << *lwit << "\"... ";
	    t_bst = loaded_bst.find(*lwit);
	    t_ht = loaded_ht.find(*lwit);
	    tt = loaded_t.find(*lwit);
	    if(!t_bst)
	      {
	        cout << "failed for DictionaryBST... ";
	      }
	    if(!t_ht)
	      {
	        cout << "failed for DictionaryHashset... ";
	      }
	    if(!tt)
	      {
	        cout << "failed for DictionaryTrie... ";
	      }
	    if(t_bst && t_ht && tt)
	      {
	        cout << "PASSED! :D ";
	      }
	    cout << endl;
	  }

	cout << endl;

    cout << endl << "Finding fifteen most common words starting w 'pre'..." << endl;

    strings = loaded_t.predictCompletions("pre", 15); 
    for(i =0 ; i < 15; i++)
        cout << strings[i] << endl;

    cout << endl;  

	return 0;
}
