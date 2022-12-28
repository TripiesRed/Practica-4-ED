//
// Created by diegoos_03 on 28/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include <vector>
#include <string>

using namespace std;

class Solver{

private:
    Dictionary dictionary;
    LettersSet info;

    bool DoIHaveTheLettersINeed (const string word, const vector<char> &available_letters);

    pair<vector<string>, int> getSolutionsLength( const vector<char> & available_letters);

    pair<vector<string>, int> getSolutionsPunt( const vector<char> & available_letters);

public:

    Solver (const Dictionary & dict, const LettersSet & letters_set);

    pair<vector<string>, int> getSolutions( const vector<char> & available_letters, bool score_game);
};


#endif //P04_JUEGO_LETRAS_SOLVER_H