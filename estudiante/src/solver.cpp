//
// Created by diegoos_03 on 28/12/22.
//
#include <string>
#include <vector>
#include <algorithm>
#include "solver.h"
#include <letters_set.h>

// Esritorio
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                              Private functions                            //
///////////////////////////////////////////////////////////////////////////////

bool Solver::DoIHaveTheLettersINeed (const string word, const vector<char> &available_letters){
    vector<char> copy_available = available_letters;
    bool letters_ok = true;

    for(int i = 0; i < word.length() && letters_ok; i++){
        vector<char>::iterator vt;
        vt = find (copy_available.begin(), copy_available.end(), word.at(i));
        if(vt == copy_available.end()){
            vt = find (copy_available.begin(), copy_available.end(), toupper(word.at(i)));
        }

        if(vt != copy_available.end()) {
            copy_available.erase(vt);
        }
        else{
            letters_ok = false;
        }
    }

    return letters_ok;
}

pair<vector<string>, int> Solver::getSolutionsLength(const vector<char> &available_letters) {

    vector<string> list;

    for(Dictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it){
        if(dictionary.exists(*it) && DoIHaveTheLettersINeed((*it), available_letters)){
                list.push_back(*it);
        }
    }
    if(!list.empty()) {
        string max = list[0];
        vector<string> sols;
        for (int i = 1; i < list.size(); i++) {
            if (max.length() < list[i].length()) {
                max = list[i];
            }
        }

        for (int i = 0; i < list.size(); i++) {
            if (max.length() == list[i].length()) {
                sols.push_back(list[i]);
            }
        }

        pair<vector<string>, int> result(sols, max.length());
        return result;
    }
    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        pair<vector<string>, int> result(sols, punt);
        return result;
    }
}

pair<vector<string>, int> Solver::getSolutionsPunt(const vector<char> &available_letters) {

    vector<string> list;

    for(Dictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it){
        if(dictionary.exists(*it) && DoIHaveTheLettersINeed((*it), available_letters)){
            list.push_back(*it);
        }
    }

    if(!list.empty()) {
        string max = list[0];
        vector<string> sols;
        for (int i = 1; i < list.size(); i++) {
            if (info.getScore(max) < info.getScore(list[i])) {
                max = list[i];
            }
        }

        for (int i = 0; i < list.size(); i++) {
            if (info.getScore(max) == info.getScore(list[i])) {
                sols.push_back(list[i]);
            }
        }

        pair<vector<string>, int> result(sols, info.getScore(max));
        return result;
    }

    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        pair<vector<string>, int> result(sols, punt);
        return result;
    }
}

pair<vector<string>, int> Solver::getSolutionsLengthEfficient(const vector<char> &available_letters) {

    vector<string> list, sols;
    int punt;
    vector <char> available_characters;
    for (int i = 0; i < available_letters.size(); ++i) {
        available_characters.push_back(std::tolower(available_letters[i]));
    }

    for(Dictionary::possible_words_iterator it = dictionary.possible_words_begin(available_characters);
        it != dictionary.possible_words_end(); ++it){
        list.push_back(*it);
    }

    if(!list.empty()) {
        string max = list[0];
        vector<string> sols;
        for (int i = 1; i < list.size(); i++) {
            if (max.length() < list[i].length()) {
                max = list[i];
            }
        }

        for (int i = 0; i < list.size(); i++) {
            if (max.length() == list[i].length()) {
                sols.push_back(list[i]);
            }
        }

        pair<vector<string>, int> result(sols, max.length());
        return result;
    }
    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        pair<vector<string>, int> result(sols, punt);
        return result;
    }
}

pair<vector<string>, int> Solver::getSolutionsPuntEfficient(const vector<char> &available_letters) {

    vector<string> list;
    vector <char> available_characters;
    for (int i = 0; i < available_letters.size(); ++i) {
        available_characters.push_back(tolower(available_letters[i]));
    }

    for(Dictionary::possible_words_iterator it = dictionary.possible_words_begin(available_characters);
        it != dictionary.possible_words_end(); ++it){
        list.push_back(*it);

    }
    if(!list.empty()) {
        string max = list[0];
        vector<string> sols;
        for (int i = 1; i < list.size(); i++) {
            if (info.getScore(max) < info.getScore(list[i])) {
                max = list[i];
            }
        }

        for (int i = 0; i < list.size(); i++) {
            if (info.getScore(max) == info.getScore(list[i])) {
                sols.push_back(list[i]);
            }
        }

        pair<vector<string>, int> result(sols, info.getScore(max));
        return result;
    }

    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        pair<vector<string>, int> result(sols, punt);
        return result;
    }
}



///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {
    dictionary = dict;
    info = letters_set;

}

pair<vector<string>, int> Solver::getSolutions(const vector<char> & available_letters, bool score_game){

    if(score_game){
        return getSolutionsPunt(available_letters);
    }
    else{
        return getSolutionsLength(available_letters);
    }
}

pair<vector<string>, int> Solver::getSolutionsEfficient(const vector<char> & available_letters, bool score_game){

    if(score_game){
        return getSolutionsPuntEfficient(available_letters);
    }
    else{
        return getSolutionsLengthEfficient(available_letters);
    }
}