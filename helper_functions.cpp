#include <helper_functions.h>

bool in_dictionary(std::vector<std::string> string_vector, std::string query)
{
    //Using a hashmap is probably faster but w/e
    int first = 0;
    int last = string_vector.size() - 1;
    int mid;

    //Since all strings are same case < and > operators can be used
    while(first <= last)
    {
        mid = first + (last - first) / 2;
        if(query < string_vector[mid])
        {
            last = mid - 1;
        }
        else if(query > string_vector[mid])
        {
            first = mid + 1;
        }
        else
        {
            return true;
        }
    }

    return false;

}

int validate_word(std::vector<std::string> dictionary, std::string query, std::unordered_map<std::string, bool> &word_guesses, Board &boggle_board)
{
    //Find word in dictionary
    for(int i = 0; i < 1; ++i)
    {

        if(word_guesses.count(query) == 0)
        {
            if(in_dictionary(dictionary, query))
            {
                word_guesses.insert({query, true});
            }
            else
            {
                //unrecognized word
                return -1;
            }
        }
        else
        {
            //already guessed
            return -2;
        }

    }

    //Find word in boggle board
    int directions[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0,1}, {1, -1}, {1, 0}, {1,1}};
    Block current_block;
    std::unordered_map<std::string, bool> visited_blocks;

    for(int i = 0; i < 16; ++i)
    {
        bool word_found = false;
        int current_index = 0;
        int x = i / 4;
        int y = i % 4;
        int dx = x;
        int dy = y;
        std::vector<int> moves;
        std::string free_block = "";

        if(boggle_board.get_block(x, y).get_face() == toupper(query[current_index]))
        {
            current_block = boggle_board.get_block(x, y);
            visited_blocks.insert({current_block.get_sides(), true});
            do
            {
                //Check letters around current block
                for(int j = 0; j < 8; ++j)
                {
                    dx = directions[j][0];
                    dy = directions[j][1];

                    //check if block being accessed is inside the board and has not already been accessed
                    if(x + dx >= 0 && x + dx < 4 && y + dy >= 0 && y + dy < 4 && visited_blocks.count(boggle_board.get_block(x + dx, y + dy).get_sides()) == 0)
                    {
                        //word was found
                        if(current_index == query.length() - 1)
                        {
                            word_found = true;
                            current_index = 0;
                            break;
                        }
                        //adjacent block is the next letter in the string
                        else if(current_index != query.length() - 1 && boggle_board.get_block(x + dx, y + dy).get_face() == toupper(query[current_index + 1]))
                        {
                            ++current_index;
                            moves.push_back(j);
                            current_block = boggle_board.get_block(x + dx, y + dy);
                            visited_blocks.erase(free_block);
                            visited_blocks.insert({current_block.get_sides(), true});
                            x += dx;
                            y += dy;
                            //reset loop, j will be incremented back to 0 for next iteration
                            j = -1;

                        }


                    }
                    //next letter was not found, try again at the block before
                    //this will only be true if the next letter was not found; the "word not found" condition breaks the loop and the
                    //"next letter in string found" condition resets j back to zero.
                    if(j == 7)
                        {
                            //If on the first block, then there is no previous block to go to; move onto next block in boggle grid
                            if(current_index == 0)
                            {
                                break;
                            }

                            //since the current block failed, it is not part of the final path of blocks (or at least not yet), and must be removed from the hashmap when the previous
                            //block takes a different route, so that future blocks are able to access it
                            free_block = current_block.get_sides();

                            //move back one block
                            int previous = moves[current_index - 1];
                            current_block = boggle_board.get_block(x - directions[previous][0], y - directions[previous][1]);
                            x -= directions[previous][0];
                            y -= directions[previous][1];
                            --current_index;
                            moves.pop_back();
                            //reset loop
                            j = -1;
                        }
                }

            }while(current_index != 0);
        }

        if(word_found)
        {
            //success
            return 1;
        }
        else
        {
           //map must be cleared after each block visit to reset any blocks marked as visited that no longer have been
           //O O O A
           //O A U R
           //O O O O
           //O O O O
           //eg. searching for "aura" in the above grid would lead to an infinite loop since the A in the top row would be
           //marked as "visited" when it was accessed as the potential first letter by the outermost for loop
           visited_blocks.clear();
        }

    }

    //all blocks were checked and word was not found in boggle board
    return -3;
}
