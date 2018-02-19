#include "util.h"
#include "DictionaryTrie.h"
#include <algorithm>

/*  Dictionary in form of mwt
    Yash Nevatia & Josh Hunter
    20 April 2017
*/

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(): root(new TrieNode) {}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 *"Invalid Input. Please retry with correct input") */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
    
    if (word.empty())
        return false;

    // traverse trie to last added letter
    pair<unsigned int, TrieNode*> lastNode = iterateTo(word);
    unsigned int i = lastNode.first;
    TrieNode * curr = lastNode.second;

    // duplicate case
    if (i == word.length() && curr->word) {
        if (freq > curr->freq)
            curr->freq = freq;
        return false;
    }

    char letter;

    // add remaining letters to trie, one node at a time
    while (i < word.length()) {
        letter = word.at(i);

        if (letter == ' ') // space case
            letter = '{';

        // new node for character
        (curr->letters).at(letter - 'a') = new TrieNode;

        // iteration to next node
        curr = (curr->letters).at(letter - 'a');

        i++;
    }

    curr->word = true;
    curr->freq = freq;

    return true;
}

pair<unsigned int, TrieNode *> DictionaryTrie::iterateTo(std::string word) const{
    TrieNode * curr = root;
    unsigned int i = 0;
    char letter;

    while (i < word.length()) {
        letter = word.at(i);

        if (letter == ' ') // space case
            letter = '{';

        int numltr = letter - 'a';

        if (numltr > ALPHABET_SIZE || numltr < 0) { // case for special characters
            std::cout << "Invalid Input. Please retry with correct input" << std::endl;
            return make_pair(-1, curr);
        }

        if (((curr->letters).at(numltr)) == nullptr)
            return make_pair(i, curr);

        curr = (curr->letters).at(numltr);
        i++;
    }

    return make_pair(i, curr);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
    std::pair<unsigned int, TrieNode*> lastNode = iterateTo(word);
    return (lastNode.first == word.length()) && ((lastNode.second)->word);
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions) {
    std::vector <std::string> words;
    set <pair<unsigned int, std::string>> wordpairs;
    pair <unsigned int, std::string> prefixword;

    if (prefix.empty()) { // case that prefix is empty
        std::cout << "Invalid Input. Please retry with correct input" << std::endl;
        return words;
    }

    // traverse trie to last added letter
    pair<unsigned int, TrieNode*> lastNode = iterateTo(prefix);

    if(lastNode.first < prefix.length())
        return words; // case that prefix wasn't reached

    TrieNode * curr = lastNode.second;

    wordpairs = getWords(prefix, curr); // gets potential words

    // case that there are fewer completions than requested
    if (wordpairs.size() < num_completions)
        num_completions = wordpairs.size();

    // sort the set by frequency

    set <pair<unsigned int, std::string>>::iterator it = wordpairs.end();

    for (unsigned int i = 0; i < num_completions; i++) {
        it--;
        words.push_back(it->second);
    }

    return words;
}

// recurive helper funciton to find words with prefix `prefix`
set<pair<unsigned int, std::string>> DictionaryTrie::getWords(std::string prefix, TrieNode * curr) {
    set<pair<unsigned int, std::string>> words;
    set<pair<unsigned int, std::string>> newwords;
    char letter;

    if(curr->word) // case that the prefix is a word
        words.insert(std::make_pair(curr->freq, prefix));

    // recursively iterates through trie finding appropriate words
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
        
        if (i == 26) letter = ' '; // case for space
        else letter = i + 'a';

        if ((curr->letters).at(i)) { // checks if node has this character
            newwords = getWords(prefix + letter, (curr->letters).at(i));
            words.insert(newwords.begin(), newwords.end());
        }
    }

    return words;
}

void DictionaryTrie::deleteAllNodes(TrieNode * curr) {
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
        if ((curr->letters).at(i) != nullptr)
            deleteAllNodes((curr->letters).at(i));
    delete(curr);
}

/* Destructor */
DictionaryTrie::~DictionaryTrie() {
    deleteAllNodes(root);
}
