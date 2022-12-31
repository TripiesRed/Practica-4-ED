//
// Created by gonzalomp on 30/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H
#define P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H

#include "dictionary.h"
#include <letters_set.h>
#include "letters_bag.h"
#include <vector>
#include <string>

using namespace std;

class SolverEficiente{

private:
    Dictionary dictionary;
    LettersSet info;

    pair<vector<string>, int> getSolutionsLength( const vector<char> & available_letters);

    pair<vector<string>, int> getSolutionsPunt( const vector<char> & available_letters);

public:

    SolverEficiente (const Dictionary & dict, const LettersSet & letters_set);

    pair<vector<string>, int> getSolutions( const vector<char> & available_letters, bool score_game);
};

#endif //P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H
