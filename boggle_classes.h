#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

/* Class representing a six sided die, with each face displaying a different letter */
class Block
{
    private:
        std::string sides;
        char face;

    public:
        Block& operator=(const Block& other);
        void set_sides(std::string sSides);
        void random_face();
        char get_face();
        std::string get_sides();
};

/* Class representing the actual boggle board, a 4x4 array of dice */
class Board
{
    private:
        std::string letters[16] = {"RIFOBX", "IFEHEY", "DENOWS", "UTOKND",
                               "HMSRAO", "LUPETS", "ACITOA", "ULGKUE",
                               "QBMJOA", "EHISPN", "VETIGN", "BALIYT",
                               "EZAVND", "RALESC", "UWILRG", "PACEMD"};
        Block grid[4][4];

    public:
        void random_config();
        void print_grid();
        Block get_block(int x, int y);

};
