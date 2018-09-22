#include "helper_functions.h"

int main()
{
    srand(time(NULL));

    Board boggle_board;
    boggle_board.random_config();
    boggle_board.print_grid();


    std::unordered_map<std::string, bool> word_guesses;
    std::vector<std::string> dictionary;
    std::ifstream file("words_alpha.txt");
    std::string word;
    while(std::getline(file, word))
    {
        //Max word length in boggle is 16, min is 3
        if(word.length() >= 3 && word.length() <= 16)
        {
            dictionary.push_back(word);
        }
    }

    int score = 0;
    std::string input = "";
    std::cout << "Enter \"@quit\" to exit.\n";

    while(input != "@quit")
    {
        std::cout << "Enter word: ";
        std::cin >> input;

        switch(validate_word(dictionary, input, word_guesses, boggle_board))
        {
            case -3: std::cout << "Word not found in board.\n";
                     break;
            case -2: std::cout << "Word already guessed.\n";
                     break;
            case -1: std::cout << "Word not found in dictionary. \n";
                     break;
            case  1:
                std::cout << input << ": ";
                switch(input.length())
                    {
                        case 3:
                        case 4: std::cout << "1 point.";
                                score++;
                                break;
                        case 5: std::cout << "2 points.";
                                score += 2;
                                break;
                        case 6: std::cout << "3 points.";
                                score += 3;
                                break;
                        case 7: std::cout << "5 points.";
                                score += 5;
                                break;
                        default: std::cout << "11 points.";
                                 score += 11;

                    }
                std::cout << "\n";
        }
        std::cout << "Score: " << score << "\n";
    }
}
