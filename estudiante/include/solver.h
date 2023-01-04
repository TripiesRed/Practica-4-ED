//
// Created by diegoos_03 on 28/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "dictionary.h"
#include <letters_set.h>
#include "letters_bag.h"
#include <vector>
#include <string>

using namespace std;

/**
 * Clase que representa un solver del juego de las letras.
 *
 * @param dictionary almacena las palabras válidas.
 * @param info contiene la cantidad y puntos de cada letra.
 */
class Solver{

private:
    Dictionary dictionary;
    LettersSet info;

    /**
     * @brief Comprueba si a partir de available_letters se puede construir la palabra word.
     * @param word Palabra que se pretende construir.
     * @param available_letters Letras de las que se dispone para crear la palabra.
     * @return Devuelve true si se puede crear la palabra, false en caso contrario.
     */
    bool DoIHaveTheLettersINeed (const string word, const vector<char> &available_letters);

    /**
     * @brief Dadas las letras disponibles, obtiene las soluciones según el modo Longitud.
     * @param available_letters Letras de las que se dispone para obtener las soluciones.
     * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
     */
    pair<vector<string>, int> getSolutionsLength( const vector<char> & available_letters);

    /**
    * @brief Dadas las letras disponibles, obtiene las soluciones según el modo Puntuación.
    * @param available_letters Letras de las que se dispone para obtener las soluciones.
    * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
    */
    pair<vector<string>, int> getSolutionsPunt( const vector<char> & available_letters);

    /**
     * @brief Dadas las letras disponibles, obtiene las soluciones de forma eficiente según el modo Longitud.
     * @param available_letters Letras de las que se dispone para obtener las soluciones.
     * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
     */
    pair<vector<string>, int> getSolutionsLengthEfficient( const vector<char> & available_letters);

    /**
    * @brief Dadas las letras disponibles, obtiene las soluciones de forma eficiente según el modo Puntuación.
    * @param available_letters Letras de las que se dispone para obtener las soluciones.
    * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
    */
    pair<vector<string>, int> getSolutionsPuntEfficient( const vector<char> & available_letters);

public:

    /**
     * @brief Constructor de un objeto solver.
     * @param dict Diccionario donde se guardan las palabras válidas.
     * @param letters_set Objeto letter_set donde se guarda información sobre las letras.
     */
    Solver (const Dictionary & dict, const LettersSet & letters_set);

    /**
    * @brief Dadas las letras disponibles, obtiene las soluciones según el modo que se especifique en score_game.
    * @param available_letters Letras de las que se dispone para obtener las soluciones.
    * @param score_game true si se juega a puntuación, false si se juega a longitud.
    * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
    */
    pair<vector<string>, int> getSolutions( const vector<char> & available_letters, bool score_game);

    /**
    * @brief Dadas las letras disponibles, obtiene las soluciones de forma eficiente según el modo que se especifique en score_game.
    * @param available_letters Letras de las que se dispone para obtener las soluciones.
    * @param score_game true si se juega a puntuación, false si se juega a longitud.
    * @return Pareja compuesta de un vector de palabras (soluciones), y un número que indica la puntuación de las soluciones.
    */
    pair<vector<string>, int> getSolutionsEfficient( const vector<char> & available_letters, bool score_game);
};


#endif //P04_JUEGO_LETRAS_SOLVER_H