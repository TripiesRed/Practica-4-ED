//
// Created by gonzalomp on 30/12/22.
//

#include "solver_eficiente.h"
#include <string>
#include <vector>
#include <letters_set.h>
#include <dictionary.h>
#include "letters_bag.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                              Private functions                            //
///////////////////////////////////////////////////////////////////////////////

pair<vector<string>, int> SolverEficiente::getSolutionsLength(const vector<char> &available_letters) {

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
        for (int i = 1; i <= list.size(); i++) {
            if (max.length() < list[i].length()) {
                max = list[i];
            }
        }

        for (int i = 0; i <= list.size(); i++) {
            if (max.length() == list[i].length()) {
                sols.push_back(list[i]);
            }
        }

        std::pair<vector<string>, int> result(sols, max.length());
        return result;
    }
    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        std::pair<vector<string>, int> result(sols, punt);
        return result;
    }
}

pair<vector<string>, int> SolverEficiente::getSolutionsPunt(const vector<char> &available_letters) {

    vector<string> list;
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
            if (info.getScore(max) < info.getScore(list[i])) {
                max = list[i];
            }
        }

        for (int i = 0; i < list.size(); i++) {
            if (info.getScore(max) == info.getScore(list[i])) {
                sols.push_back(list[i]);
            }
        }

        std::pair<vector<string>, int> result(sols, info.getScore(max));
        return result;
    }

    else{
        vector<string> sols;
        sols.clear();
        int punt = 0;
        std::pair<vector<string>, int> result(sols, punt);
        return result;
    }
}



///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

SolverEficiente::SolverEficiente(const Dictionary &dict, const LettersSet &letters_set) {
    dictionary = dict;
    info = letters_set;

}

pair<vector<string>, int> SolverEficiente::getSolutions(const vector<char> & available_letters, bool score_game){

    if(score_game) return getSolutionsPunt(available_letters);

    else return getSolutionsLength(available_letters);
}