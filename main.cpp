#include <GLFW/glfw3.h>
#include "Game.h"


int main(void)
{
    Game game(600, 600, "Snake Game");
    
    while (!game.gameShouldClose())
    {
        game.run();
    }
    exit(EXIT_SUCCESS);
}