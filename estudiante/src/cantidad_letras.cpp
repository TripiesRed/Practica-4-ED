//
// Created by diegoos_03 on 27/12/22.
//
#include <fstream>
#include <iostream>

#include "dictionary.h"
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{

    if(argc != 3){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero de letras" << endl;
        exit(-1);
    }

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

    int usages;
    int ocurrences;

    for(char c = 'A'; c <= 'Z'; c++){
        usages = diccionario.getTotalUsages(c);
        ocurrences = diccionario.getOccurrences(c);

        cout << c << "\t" << usages << "\t" << ocurrences;

    }

}