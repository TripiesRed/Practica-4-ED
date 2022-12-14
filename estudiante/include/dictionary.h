//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {
private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character in that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        inline bool operator==(const char_info &rhs) {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        inline bool operator*() { return this->character; }

        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Calcula el número de ocurrencias a partir de un nodo del carácter que se pasa como argumento en el árbol de forma recursiva.
     * @param c Carácter del que se calcula las ocurrencias.
     * @param current Nodo a partir del cual se calculan las ocurrencias.
     * @return Número de ocurrencias del caracter.
     */
    int getOccurrences(node curr_node, char c);

    /**
     * @brief Calcula el número de usos a partir de un nodo del carácter que se pasa como argumento en el árbol de forma recursiva.
     * @param c Carácter del que se calcula los usos.
     * @param current Nodo a partir del cual se calculan los usos.
     * @return Pareja compuesta por el número de ocurrencias del carácter en los nodos que cuelgan del nodo actual,
     * y el número de palabras que terminan por debajo del nodo actual.
     */
    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Calcula el número de ocurrencias del carácter que se pasa como argumento en el árbol de forma recursiva.
     * @param c Carácter del que se calcula las ocurrencias.
     * @return Número de ocurrencias del caracter.
     */
    int getOccurrences(const char c);

    /**
     * @brief Calcula el número de usos del carácter que se pasa como argumento en el árbol de forma recursiva.
     * @param c Carácter del que se calcula los usos.
     * @return Número de usos del caracter.
     */
    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    class iterator {
    private:
        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:
        /**
         * @brief Constructor por defecto.
         */
        iterator();

        /**
         * @brief Constructor de copia
         * @param iter Iterador que se copia.
         */
        iterator(tree<char_info>::const_preorder_iterator iter);

        /**
         * @brief Obtiene el contenido del iterador.
         * @return Devuelve la palabra sobre la que se posiciona el iterador.
         */
        std::string operator*();

        /**
         * @brief Avanza hacia el siguiente iterador.
         * @return Devuelve el siguiente iterador.
         */
        iterator &operator++();

        /**
         * @brief Comprueba si los iteradores son iguales.
         * @param other El iterador con el que se compara.
         * @return true si son iguales, false en caso contrario.
         */
        bool operator==(const iterator &other) const;

        /**
         * @brief Comprueba si los iteradores son iguales.
         * @param other El iterador con el que se compara.
         * @return false si son iguales, true en caso contrario.
         */
        bool operator!=(const iterator &other) const;

    };

    /**
     * @brief Iterador a la primera palabra del diccionario.
     * @return Devuelve un iterador a la primera palabra del diccionario.
     */
    iterator begin() const;

    /**
     * @brief Apunta a la siguiente de la última palabra del diccionario.
     * @return Devuelve un iterador que apunta a la siguiente de la última palabra del diccionario.
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    class possible_words_iterator {
    public:

        /**
         * @brief Constructor por defecto.
         */
        possible_words_iterator();

        /**
         * @brief Constructor con parámetros
         * @param current_node Nodo en el que va a comenzar el iterador.
         * @param available_letters Vector de caracteres disponibles para formar palabras.
         */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Constructor de copia
         * @param iter Iterador que se copia.
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Operador de asignación.
         * @param other Iterador que se va a asignar.
         * @return Devuelve una copia del iterador @p other.
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Comprueba si los iteradores son iguales.
         * @param other El iterador con el que se compara.
         * @return true si son iguales, false en caso contrario.
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Comprueba si los iteradores son iguales.
         * @param other El iterador con el que se compara.
         * @return false si son iguales, true en caso contrario.
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Avanza hacia el siguiente iterador.
         * @return Devuelve el siguiente iterador.
         */
        possible_words_iterator &operator++();

        /**
         * @brief Obtiene el contenido del iterador.
         * @return Devuelve la palabra contenida en el iterador.
         */
        string operator*() const;

    private:
        multiset<char> available_letters;
        int level;
        node current_node;
        string current_word;

        /**
         * @brief Comprueba si un caracter está disponible en @p available_letters, y si el número de ocurrencias del
         * mismo en @p current_word no supera al número de ocurrencias en @p available_letters.
         * @param c Carácter a comprobar
         * @return Booleano que indica si el caracter aún se puede usar para formar una palabra (true), o false en
         * caso de que no esté disponible o si ha sido usado todas las veces posibles.
         */
        bool disponible(const char c) const;

    };

    /**
    * @brief Iterador a la primera palabra del diccionario.
    * @return Devuelve un iterador a la primera palabra del diccionario.
    */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief Apunta a la siguiente de la última palabra del diccionario.
     * @return Devuelve un iterador que apunta a la siguiente de la última palabra del diccionario.
     */
    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP
