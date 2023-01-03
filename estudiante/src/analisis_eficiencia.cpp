//
// Created by gonzalomp on 2/01/23.
//
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "solver.h"

using namespace std;

void experiment_solver(int n, int repetitions, Dictionary dictionary, LettersSet lettersSet) {

    // Inicializamos el experimento antes del bucle de conteo de tiempo para no afectar al análisis
    LettersBag prueba (lettersSet);
    vector<char> available_letters= prueba.extractLetters(n);
    Solver solver(dictionary,lettersSet);

    //PARTE 1 - SOLVER
    // Medimos el tiempo antes de iniciar el expermiento
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // Realizamos el experimento tantas veces como indique repetitions, para tener cierta robustez
    // en el resultado (no todas las ejecuciones tardan lo mismo)
    for (int k = 0; k < repetitions; ++k){
        solver.getSolutions(available_letters,true);
    }

    // Medimos el tiempo al finalizar el experimento
    chrono::high_resolution_clock::time_point finish_time = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre el inicio y el final
    chrono::duration<double> total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Dividimos el tiempo total entre el número de repeticiones para obtener el tiempo medio por ejecución
    cout << n << "\t" << total_duration.count()/repetitions << endl;

}

void experiment_solverEficiente(int n, int repetitions, Dictionary dictionary, LettersSet lettersSet) {

    // Inicializamos el experimento antes del bucle de conteo de tiempo para no afectar al análisis
    LettersBag prueba (lettersSet);
    vector<char> available_letters= prueba.extractLetters(n);
    SolverEficiente solverEficiente(dictionary,lettersSet);

    //PARTE 1 - SOLVER
    // Medimos el tiempo antes de iniciar el expermiento
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // Realizamos el experimento tantas veces como indique repetitions, para tener cierta robustez
    // en el resultado (no todas las ejecuciones tardan lo mismo)
    for (int k = 0; k < repetitions; ++k){
        solverEficiente.getSolutions(available_letters,true);
    }

    // Medimos el tiempo al finalizar el experimento
    chrono::high_resolution_clock::time_point finish_time = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre el inicio y el final
    chrono::duration<double> total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Dividimos el tiempo total entre el número de repeticiones para obtener el tiempo medio por ejecución
    cout << n << "\t" << total_duration.count()/repetitions << endl;

}

int main(int argc, char *argv[]){

    //Entrada de argumentos
    if(argc!=3){
        cout << "Número de argumentos incorrecto: ./analisis_eficiencia <diccionario> <fich_letras>" << endl;
        exit(-1);
    }

    ifstream f_diccionario(argv[1]);

    if(!f_diccionario){
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        exit(-1);
    }

    Dictionary diccionario;
    f_diccionario >> diccionario;

    ifstream f_letras(argv[2]);

    if(!f_letras){
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        exit(-1);
    }

    LettersSet letras;
    f_letras >> letras;

    //Cálculo de los datos
    cout << "Parametros del experimento: " << argv[1] << " " << argv[2] << endl;
    cout << "Resultados para Solver: " << endl;
    for(int i=1; i<92; i+=10){
        experiment_solver(i,30,diccionario,letras);
    }

    cout << endl << "Resultados para SolverEficiente: " << endl;
    for(int i=1; i<92; i+=10){
        experiment_solverEficiente(i,30,diccionario,letras);
    }

    cout << endl << "FIN" << endl;

    return 0;
}