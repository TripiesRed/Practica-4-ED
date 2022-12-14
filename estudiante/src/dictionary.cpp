//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
    int ocurrences = 0;

    if((*curr_node).character == c){
        ocurrences++;
    }

    if(!curr_node.left_child().is_null()){
        ocurrences += getOccurrences(curr_node.left_child(), c);
    }

    if(!curr_node.right_sibling().is_null()){
        ocurrences += getOccurrences(curr_node.right_sibling(), c);
    }

    return ocurrences;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){

    int char_ocurrences = 0;
    int word_number = 0;

    std::pair<int, int> left_child (0, 0);
    std::pair<int, int> rigth_sibling (0, 0);

    if(!curr_node.left_child().is_null()){
        left_child = getTotalUsages(curr_node.left_child(), c);
    }

    if(!curr_node.right_sibling().is_null()) {
        rigth_sibling = getTotalUsages(curr_node.right_sibling(), c);
    }

    char_ocurrences = std::get<0>(left_child) + std::get<0>(rigth_sibling);
    word_number = std::get<1>(left_child) + std::get<1>(rigth_sibling);

    if((*curr_node).character == c){
        char_ocurrences += std::get<1>(left_child);
    }

    if((*curr_node).valid_word){
        word_number++;
        if((*curr_node).character == c){
            char_ocurrences ++;
        }
    }

    std::pair<int, int> result (char_ocurrences, word_number);
    return result;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << endl;
  }
  return os;
}

istream& operator>>(std::istream &is, Dictionary &dict){
  string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    node root = words.get_root();

    return getOccurrences(root, c);
}

int Dictionary::getTotalUsages(const char c){
    node root = words.get_root();

    int total_usages = std::get<0>(getTotalUsages(root, c));

    return total_usages;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() = default;

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->iter = iter;
}

std::string Dictionary::iterator::operator*() {
    return this->curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {

    do {
        int last_lvl = iter.get_level();
        ++iter;

        if (this->iter.get_level() == last_lvl) {
            this->curr_word.pop_back();
            this->curr_word += (*iter).character;
        }

        else if (this->iter.get_level() == last_lvl + 1)
            this->curr_word += (*iter).character;

        else {
            if (iter.get_level() != 0) {
                int i = 0, diff = ::abs(last_lvl - iter.get_level());
                while (i < diff) {
                    this->curr_word.pop_back();
                    i++;
                }
                this->curr_word.pop_back();
                this->curr_word += (*iter).character;
            }
            else
                this->curr_word.clear();
        }

        if(iter.get_level() == 0) return *this;

    } while (!(*iter).valid_word );


    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) const{
    bool iguales = this->iter == other.iter;
    return iguales;
}

bool Dictionary::iterator::operator!=(const iterator &other) const{
    bool distintos = this->iter != other.iter;
    return distintos;
}

Dictionary::iterator Dictionary::begin() const {
    Dictionary::iterator inicio = this->words.cbegin_preorder();
    ++inicio;
    return inicio;
}

Dictionary::iterator Dictionary::end() const {
    return this->words.cend_preorder();
}

///////////////////////////////////////////////////////////////////////////////
//                            Possible Words Iterator                               //
///////////////////////////////////////////////////////////////////////////////

Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    Dictionary::possible_words_iterator inicio(this->words.get_root(), available_characters);
    ++inicio;
    return inicio;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    Dictionary::possible_words_iterator final;
    return final;
}

Dictionary::possible_words_iterator::possible_words_iterator(){
    level = 0;
    current_word = "";
    current_node = node();
    available_letters =  multiset<char>();
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){
    this->current_node = current_node;

    int tam = available_letters.size();
    for (int i = 0; i < tam; ++i) this->available_letters.insert(available_letters[i]);

    level = 0;
    current_word = "";
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    *this = other;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    this->available_letters = other.available_letters;
    this->current_node = other.current_node;
    this->current_word = other.current_word;
    this->level = other.level;

    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    bool iguales = true;

    if ( (this->current_node!=other.current_node) || (this->current_word!=other.current_word) || (this->level!=other.level) )
        iguales = false;

    return iguales;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    bool distintos = true;

    if (*this==other) distintos = false;

    return distintos;
}

bool Dictionary::possible_words_iterator::disponible(const char c) const {
    bool available = false;
    if(count(this->current_word.begin(),this->current_word.end(),c) < this->available_letters.count(c) || this->current_word == "")
        available = true;
    return available;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

    bool valida = false; //Se??al que nos indica cuando hayamos encontrado una palabra v??lida
    node fin;
    bool still_in_same_node = false;
    do{
        //Primera iteraci??n cuando comenzamos en la ra??z para evitar que se imprima el primer elemento nulo
        if(this->level==0){
            this->current_node=this->current_node.left_child();
            this->level++;
        }

        if (!this->current_node.is_null() ) { //Comprobamos si el nodo actual es nulo

            //Comprobamos si la letra del nodo actual la podemos utilizar
            if(this->available_letters.count((*this->current_node).character)!=0 && !still_in_same_node){

                //A??adimos la letra a la palabra y la eliminamos de entre las disponibles
                this->current_word+=(*this->current_node).character;
                this->available_letters.erase(this->available_letters.find((*this->current_node).character));

                //En caso de estar en una palabra v??lida, activamos la se??al
                if((*this->current_node).valid_word) valida = true;

                //Si el hijo izquierdo del nodo actual no es nulo nos colocamos en ??l
                if (!this->current_node.left_child().is_null()) {
                    this->current_node = this->current_node.left_child();
                    level++;
                }
                //Comprobamos si hemos repetido en el mismo nodo. En caso de ser as??, corrige la palabra y busca
                // el siguiente nodo que corresponde
                else if(this->current_word.length()>3){
                    if((*this->current_node.parent().parent()).character != this->current_word.at(this->current_word.length()-3)
                        || (*this->current_node.parent()).character != this->current_word.at(this->current_word.length()-2)) {
                        still_in_same_node = true;
                        this->available_letters.insert((*this->current_node).character);
                        this->current_word.pop_back();
                        valida = false;
                    }
                }

                else if(this->current_word.length()>2){
                    if ((*this->current_node.parent()).character != this->current_word.at(this->current_word.length()-2)){
                        still_in_same_node = true;
                        this->available_letters.insert((*this->current_node).character);
                        this->current_word.pop_back();
                        valida = false;
                    }
                }

            }

            //En caso de que no podamos usar el nodo actual, nos colocamos en su hermano derecho (si no es nulo)
            else if (!this->current_node.right_sibling().is_null()){
                if(this->level != 1 && this->current_word.at(this->current_word.length()-1) == (*this->current_node).character
                    && this->level == this->current_word.length()) {
                    this->available_letters.insert((*this->current_node).character);
                    this->current_word.pop_back();
                }

                this->current_node = this->current_node.right_sibling();
                if(still_in_same_node) still_in_same_node=false; //Indicamos que hemos cambiado de nodo
            }

            //En caso de que no podamos usar el nodo actual y no tenga hermano derecho
            else{
                //Subimos por la rama actual hasta llegar al primer nodo cuyo hermano derecho no es nulo o hayamos
                //vuelto a la ra??z
                while (!this->current_node.parent().is_null() &&
                       (this->current_node.right_sibling().is_null() || this->current_node.right_sibling() == this->current_node)){

                    //Devolvemos las letras utilizadas al conjunto de letras disponibles a medida que subimos
                    if(this->level != 1 && this->current_word.at(this->current_word.length()-1) == (*this->current_node).character
                       && this->level == this->current_word.length()) {
                        this->available_letters.insert((*this->current_node).character);
                        this->current_word.pop_back();
                    }

                    //Subimos de nivel y nodo
                    this->current_node = this->current_node.parent();
                    this->level--;
                }

                //Si el nodo actual es la ra??z, entonces hemos terminado luego el nodo actual pasa ser vac??o
                if (this->current_node.parent().is_null()){
                    if(this->current_word != ""){
                        this->available_letters.insert((*this->current_node).character);
                        this->current_word.pop_back();
                    }
                    this->current_node = fin;
                }

                //Si el nodo actual tiene un hermano derecho no nulo, devolvemos la letra del nodo actual al conjunto
                // y nos posicionamos en su hermano derecho
                else {
                    this->available_letters.insert((*this->current_node).character);
                    this->current_word.pop_back();
                    this->current_node = this->current_node.right_sibling();
                }
            }
        }

        //En caso de haber vuelto a la ra??z, terminamos
        if(this->current_node == fin) return *this;

    }while(!valida || still_in_same_node); //Repetir hasta encontrar una palabra v??lida

    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return this->current_word;
}
