#include <boggle_classes.h>

//Block function definitions

Block& Block::operator=(const Block& other)
{
    sides = other.sides;
    face = other.face;
}

void Block::set_sides(std::string sSides)
{
    sides = sSides;
}

void Block::random_face()
{
   face = sides[rand() % 6];
}

char Block::get_face()
{
   return face;
}

std::string Block::get_sides()
{
    return sides;
}


//Board function definitions

void Board::random_config()
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            grid[i][j].set_sides(letters[(4 * i) + j]);
            grid[i][j].random_face();
        }

    }

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            int other_x = rand() % 4;
            int other_y = rand() % 4;
            Block temp = grid[i][j];
            grid[i][j] = grid[other_x][other_y];
            grid[other_x][other_y] = temp;
        }

    }
}

void Board::print_grid()
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << grid[i][j].get_face() << " ";
        }
        std::cout << "\n";
    }

}

Block Board::get_block(int x, int y)
{
    return grid[x][y];
}

