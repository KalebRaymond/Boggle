#include <vector>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <boggle_classes.h>

//Checks if given string query exists in string_vector
bool in_dictionary(std::vector<std::string> string_vector, std::string query);

/* Checks if given string query is a real word, has not already been guessed, and exists in the current boggle board configuration
// return -3: query was not found in boggle board
// return -2: query was previously geussed
// return -1: query does not exist as a real word in dictionary
// return  1: query is a real word, was not already guessed, and exists in the boggle board */
int validate_word(std::vector<std::string> dictionary, std::string query, std::unordered_map<std::string, bool> &word_guesses, Board &boggle_board);

