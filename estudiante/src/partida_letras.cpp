#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "solver.h"

using namespace std;

int main(int argc, char *argv[]){

    if(argc != 5){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero de letras" << endl;
        cout << "3.- L o P (modo de juego)" << endl;
        cout << "4.- Cantidad de letras para la partida" << endl;
        exit(-1);
    }

    char mode = *(argv[3]);

    int letters_amount = atoi(argv[4]);

    ifstream f_diccionario(argv[1]);

    if(!f_diccionario){
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        exit(-1);
    }

    ifstream f_letras(argv[2]);

    if(!f_letras){
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        exit(-1);
    }

    Dictionary diccionario;
    f_diccionario >> diccionario;

    LettersSet letras;
    f_letras >> letras;

    LettersBag bag(letras);
    vector <char> available = bag.extractLetters(letters_amount);

    Solver solver(diccionario, letras);

    pair<vector<string>, int> solutions;

    if(mode == 'P'){
        solutions = solver.getSolutions(available, true);
    }
    else{
        solutions = solver.getSolutions(available, false);
    }

    // SALIDA

    cout << "LETRAS DISPONIBLES:" << endl;
    for (int i = 0; i < available.size(); i++){
        cout << available[i] << " ";
    }

    cout << endl;
    cout << "SOLUCIONES:" << endl;
    for(int i = 0; i < std::get<0>(solutions).size(); i++){
        cout << std::get<0>(solutions)[i] << endl;
    }
    cout << "PUNTUACION:" << endl;
    cout << std::get<1>(solutions) << endl;

    f_diccionario.close();
    f_letras.close();

    return 0;
}