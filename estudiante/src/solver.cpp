//
// Created by diegoos_03 on 28/12/22.
//
#include <string>
#include <vector>
#include <algorithm>
#include "solver.h"
#include <letters_set.h>
#include "letters_bag.h"

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

    string max = list[0];
    vector<string> sols;
    for(int i = 1; i <= list.size(); i++){
        if(max.length() < list[i].length()){
            max = list[i];
        }
    }

    for(int i = 0; i<= list.size(); i++){
        if(max.length() == list[i].length()){
            sols.push_back(list[i]);
        }
    }

    std::pair<vector<string>, int> result (sols, max.length());
    return result;
}

pair<vector<string>, int> Solver::getSolutionsPunt(const vector<char> &available_letters) {

    vector<string> list;

    for(Dictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it){
        if(dictionary.exists(*it) && DoIHaveTheLettersINeed((*it), available_letters)){
            list.push_back(*it);
        }
    }

    string max = list[0];
    vector<string> sols;
    for(int i = 1; i <= list.size(); i++){
        if(info.getScore(max) < info.getScore(list[i])){
            max = list[i];
        }
    }

    for(int i = 0; i<= list.size(); i++){
        if(info.getScore(max) == info.getScore(list[i])){
            sols.push_back(list[i]);
        }
    }

    std::pair<vector<string>, int> result (sols, info.getScore(max));
    return result;

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