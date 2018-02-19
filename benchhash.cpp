#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <map>
#include "util.h"

#define NUMARGS 3

/*  main for benchhash testing/comparing hashtables
    Yash Nevatia & Josh Hunter
    20 April 2017
*/

using namespace std;

// gets the average with use of a step map and number of words
double getAverage(map<int, int> steps, int numWords){

    int sum = 0;

    for(auto const& step : steps){
       sum += step.first * step.second;
    }

    double rtn = (double) sum / (double) numWords;
    return rtn;
}

/* source: http://www.cse.yorku.ca/~oz/hash.html */
unsigned int yashhash(string str, unsigned int table_size) {
    unsigned int hash = 5381;
    int c;

    for(unsigned int i = 0; i < str.length(); i++ ){
        c = str.at(i);
    	hash = ((hash << 5) + hash) + c;
    }

    return hash % table_size;
}

/* source: CSE 100 lectures, Paul Cao. */
unsigned int joshhash(string key, unsigned int table_size) {

    unsigned int hashVal = 0;

    for(unsigned int i = 0; i < key.length(); i++ )
        hashVal = hashVal + (int) key.at(i);

    return hashVal % table_size;
}

// tests both hash functions
int test() {
    
    string str = "this is a test";
    unsigned int table_size = 14;
    
    // test if the return is within table size
    cout << "Testing within table sizes" << endl;
    if(yashhash(str, table_size) >= table_size) {
        cout << "Yash hashed out of bounds" << endl;
        return -1;
    }
    if(joshhash(str, table_size) >= table_size) {
        cout << "Josh hashed out of bounds" << endl;
        return -1;
    }
    cout << "PASSED" << endl << endl;
    
    // test if returns same on same input
    cout << "Testing uniformity" << endl;
    if(yashhash(str, table_size) != yashhash(str, table_size)){
        cout << "Yash's hashing isn't uniform" << endl;
        return -1;
    }
    if(joshhash(str, table_size) != joshhash(str, table_size)){
        cout << "Yash's hashing isn't uniform" << endl;
        return -1;
    }
    cout << "PASSED" << endl << endl;

    // test on yash, josh, and hash
    cout << "Yash hash size 5 on ..." << endl;
    cout << "yash: " << yashhash("yash", 5) << endl;
    cout << "hash: " << yashhash("hash", 5) << endl;
    cout << "josh: " << yashhash("josh", 5) << endl << endl;

    cout << "Josh hash size 5 on ..." << endl;
    cout << "yash: " << joshhash("yash", 5) << endl;
    cout << "hash: " << joshhash("hash", 5) << endl;
    cout << "josh: " << joshhash("josh", 5) << endl << endl;

    cout << "Yash hash size 17 on ..." << endl;
    cout << "yash: " << yashhash("yash", 17) << endl;
    cout << "hash: " << yashhash("hash", 17) << endl;
    cout << "josh: " << yashhash("josh", 17) << endl << endl;

    cout << "Josh hash size 17 on ..." << endl;
    cout << "yash: " << joshhash("yash", 17) << endl;
    cout << "hash: " << joshhash("hash", 17) << endl;
    cout << "josh: " << joshhash("josh", 17) << endl << endl;

    cout << "Yash hash size 11 on ..." << endl;
    cout << "tomato: " << yashhash("tomato", 11) << endl;
    cout << "dolphin: " << yashhash("dolphin", 11) << endl;
    cout << "popcorn: " << yashhash("popcorn", 11) << endl << endl;

    cout << "Josh hash size 11 on ..." << endl;
    cout << "tomato: " << joshhash("tomato", 11) << endl;
    cout << "dolphin: " << joshhash("dolphin", 11) << endl;
    cout << "popcorn: " << joshhash("popcorn", 11) << endl << endl;

    cout << "Yash hash size 149 on ..." << endl;
    cout << "tomato: " << yashhash("tomato", 149) << endl;
    cout << "dolphin: " << yashhash("dolphin", 149) << endl;
    cout << "popcorn: " << yashhash("popcorn", 149) << endl << endl;

    cout << "Josh hash size 149 on ..." << endl;
    cout << "tomato: " << joshhash("tomato", 149) << endl;
    cout << "dolphin: " << joshhash("dolphin", 149) << endl;
    cout << "popcorn: " << joshhash("popcorn", 149) << endl << endl;

    return 0;
}

// runs tests and/or compares two hash functions
int main(int argc, char ** argv){

    // uncomment below for testing:
    // if(!test()) cout << "All tests passed!" << endl;
    // else cout << "Test(s) failed" << endl;

    int j = 0;

    //Check number of arguments
    if(argc != NUMARGS){
        cout << "Wrong number of arguments" << endl;
        return -1;
    }

    while(argv[2][j] != '\0') { // checks if argument is number
       if(!isdigit(argv[2][j])) {
           cout << "Argument not a number" << endl;
           return -1;
       }
       j++;
    }

    int num_words = stoi(argv[2]);
    string dictfile = "../";
    dictfile.append(argv[1]);
    ifstream file(dictfile);

    if(!file.good()){ // checks if file exists
        cout << "File not found" << endl;
        return -1;
    }

    int size = 2*num_words;
    vector<string> words;
    vector<int> yash_collisions = vector<int>(size);
    vector<int> josh_collisions = vector<int>(size);
    Utils::load_vector(words, file, num_words);

    for(string word : words) { // counts collisions on inserted words
        yash_collisions.at(yashhash(word, size))++;
        josh_collisions.at(joshhash(word, size))++;
    }

    //index reps the num of hits and value is the num of slots that have that num of hits
    map<int, int> yash_buckhits; 
    map<int, int> josh_buckhits; 
    map<int, int> yash_steps; 
    map<int, int> josh_steps; 

    for (int i=0; i < size; i++){ //counts number or buckets by collisions
        int key = yash_collisions.at(i);

        if(yash_buckhits.find(key) == yash_buckhits.end())
             yash_buckhits.insert(make_pair(key,1));
        else
            (yash_buckhits.at(yash_collisions.at(i)))++;

        key = josh_collisions.at(i);

        if(josh_buckhits.find(key) == josh_buckhits.end())
             josh_buckhits.insert(make_pair(key,1));
        else
            (josh_buckhits.at(josh_collisions.at(i)))++;
    }

    cout << "Print the statistics for yashhash with table size " << size << endl;
    cout << "# hits \t# slots receiving the hits" << endl;
    for(auto const& yashbucket: yash_buckhits){ // prints and averages collisions
        cout << yashbucket.first << '\t' << yashbucket.second << endl;


        int i = yashbucket.first, sum = yashbucket.second;
        map<int, int>::reverse_iterator it = yash_buckhits.rbegin();
        while (it->first > i){
            sum += it->second;
            it++;
        }

        yash_steps.insert(make_pair(i, sum));

    }

    double yash_avg = getAverage(yash_steps, num_words);
    int yash_wst = (yash_buckhits.rbegin())->first;
    cout << "The average number of steps for a successful search for yashhash would be " << yash_avg << endl;
    cout << "The worst case steps that would be needed to find a word is " << yash_wst << endl << endl;
 
    cout << "Print the statistics for joshhash with table size " << size << endl;
    cout << "# hits \t# slots receiving the hits" << endl;
    for(auto const& joshbucket: josh_buckhits){ // prints and averages collsions
        cout << joshbucket.first << '\t' << joshbucket.second << endl;

        int i = joshbucket.first, sum = joshbucket.second;
        map<int, int>::reverse_iterator it = josh_buckhits.rbegin();
        while (it->first > i){
            sum += it->second;
            it++;
        }

        josh_steps.insert(make_pair(i, sum));

    }
 
    double josh_avg = getAverage(josh_steps, num_words);
    int josh_wst = (josh_buckhits.rbegin())->first;
    cout << "The average number of steps for a successful search for joshhash would be " << josh_avg << endl;
    cout << "The worst case steps that would be needed to find a word is " << josh_wst << endl;
}
