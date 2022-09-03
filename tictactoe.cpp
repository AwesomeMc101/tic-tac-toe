#include <iostream>
#include <vector>
#include <string>

class Game
{
public:
    std::vector<int> locationsUsedPlayer;
    std::vector<int> locationsUsedBot;
    int character = 0; // 1 = X, 2 = O
};


/*

-----------
| x  o  x |
| x  o  x |
| o  x  o |
-----------


*/

namespace Drawing
{
    void drawGame(Game gme)
    {
        std::vector<std::string> rows = { "You are: ", "-----------",
            "| 1  2  3 |", "| 4  5  6 |", "| 7  8  9 |",
             "-----------"};

        char player = 'O', bot = 'X';
        if (gme.character == 1)
        {
            player = 'X';
            bot = 'O';
        }

        rows[0] += player;

        for (int i : gme.locationsUsedBot)
        {
            std::string place = std::to_string(i);

            for (int rown = 0; rown < rows.size(); rown++)
            {
                if (rows[rown].find(place) != std::string::npos)
                {
                    size_t loc = rows[rown].find(place);
                    rows[rown][loc] = bot;
                }
            }
            
        }
        for (int i : gme.locationsUsedPlayer)
        {
            std::string place = std::to_string(i);

            for (int rown = 0; rown < rows.size(); rown++)
            {
                if (rows[rown].find(place) != std::string::npos)
                {
                    size_t loc = rows[rown].find(place);
                    rows[rown][loc] = player;
                }
            }

        }

        for (std::string row : rows)
        {
            std::cout << row << std::endl;
        }
        
    }
}

namespace Checking
{
    bool checkItem(std::vector<int> vector, int i)
    {
        return (std::find(vector.begin(), vector.end(), i) != vector.end());
    }
    bool checkCat(Game gme)
    {
        int total = 0;
        for (int i : gme.locationsUsedBot)
        {
            total += i;
        }
        for (int i : gme.locationsUsedPlayer)
        {
            total += i;
        }
        if(total > 44)
        {
            return true;
        }
        return false;
    }
    bool didWin(Game gme)
    {
        //1 , 2 , 3
        /*for (int i : gme.locationsUsedPlayer)
        {
            if
        }*/

        std::vector<int> player = gme.locationsUsedPlayer; //clean up

        if (
            checkItem(player, 1) && checkItem(player, 2) && checkItem(player, 3)
            )
        {
            return true;
        }
        if (
            checkItem(player, 4) && checkItem(player, 5) && checkItem(player, 6)
            )
        {
            return true;
        }
        if (
            checkItem(player, 7) && checkItem(player, 8) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 1) && checkItem(player, 4) && checkItem(player, 7)
            )
        {
            return true;
        }
        if (
            checkItem(player, 2) && checkItem(player, 5) && checkItem(player, 8)
            )
        {
            return true;
        }
        if (
            checkItem(player, 3) && checkItem(player, 6) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 1) && checkItem(player, 5) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 3) && checkItem(player, 5) && checkItem(player, 7)
            )
        {
            return true;
        }
        return false;
    }
    bool didBotWin(Game gme)
    {
        //1 , 2 , 3
        /*for (int i : gme.locationsUsedPlayer)
        {
            if
        }*/

        std::vector<int> player = gme.locationsUsedBot; //clean up

        if (
            checkItem(player, 1) && checkItem(player, 2) && checkItem(player, 3)
            )
        {
            return true;
        }
        if (
            checkItem(player, 4) && checkItem(player, 5) && checkItem(player, 6)
            )
        {
            return true;
        }
        if (
            checkItem(player, 7) && checkItem(player, 8) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 1) && checkItem(player, 4) && checkItem(player, 7)
            )
        {
            return true;
        }
        if (
            checkItem(player, 2) && checkItem(player, 5) && checkItem(player, 8)
            )
        {
            return true;
        }
        if (
            checkItem(player, 3) && checkItem(player, 6) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 1) && checkItem(player, 5) && checkItem(player, 9)
            )
        {
            return true;
        }
        if (
            checkItem(player, 3) && checkItem(player, 5) && checkItem(player, 7)
            )
        {
            return true;
        }
        return false;
    }
}

namespace Input
{
    void askUser(Game& gme)
    {
    entry:
        std::cout << "\nWhere do you want to go? (Enter the number of the location) || ";
        int loc;
        std::cin >> loc;
        if (loc > 0 && loc < 10)
        {
            for (int i : gme.locationsUsedPlayer)
            {
                if (i == loc)
                {
                    std::cout << "Location already taken! Try again.\n";
                    goto entry;
                }
            }
            for (int i : gme.locationsUsedBot)
            {
                if (i == loc)
                {
                    std::cout << "Location already taken! Try again.\n";
                    goto entry;
                }
            }
            gme.locationsUsedPlayer.push_back(loc);
        }
        else
        {
            std::cout << "Not a real location! Try again.\n";
            goto entry;
        }
    }

    void botGo(Game& gme)
    {
    entry:
        int loc = rand() % 9 + 1;
        for (int i : gme.locationsUsedPlayer)
        {
            if (i == loc)
            {
                goto entry;
            }
        }
        for (int i : gme.locationsUsedBot)
        {
            if (i == loc)
            {
                goto entry;
            }
        }
        gme.locationsUsedBot.push_back(loc);
    }

}

int main()
{
    srand(time(0));
    Game newGame;
    
    while (1)
    {
        if (Checking::checkCat(newGame))
        {
            system("cls");
            Drawing::drawGame(newGame);
            std::cout << "Cats game! Nobody wins :(. Starting a new game when you're ready!" << std::endl;
            std::cin.get(); std::cin.get();
            newGame.character = 1;
            newGame.locationsUsedBot.clear();
            newGame.locationsUsedPlayer.clear();
            continue;
        }
        system("cls");
        Drawing::drawGame(newGame);
        Input::askUser(newGame);
        if (Checking::didWin(newGame))
        {
            system("cls");
            Drawing::drawGame(newGame);
            std::cout << "You won! Starting a new game when you're ready!" << std::endl;
            std::cin.get(); std::cin.get();
            newGame.character = 1;
            newGame.locationsUsedBot.clear();
            newGame.locationsUsedPlayer.clear();
            continue;
        }
        Input::botGo(newGame);
        if (Checking::didBotWin(newGame))
        {
            system("cls");
            Drawing::drawGame(newGame);
            std::cout << "You lost. :(. Starting a new game when you're ready!" << std::endl;
            std::cin.get(); std::cin.get();
            newGame.character = 1;
            newGame.locationsUsedBot.clear();
            newGame.locationsUsedPlayer.clear();
            continue;
        }
        if (Checking::checkCat(newGame))
        {
            system("cls");
            Drawing::drawGame(newGame);
            std::cout << "Cats game! Nobody wins :(. Starting a new game when you're ready!" << std::endl;
            std::cin.get(); std::cin.get();
            newGame.character = 1;
            newGame.locationsUsedBot.clear();
            newGame.locationsUsedPlayer.clear();
            continue;
        }
    }
}
