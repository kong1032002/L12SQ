#include "CommonFunction.h"

int main(int argc, char* argv[])
{
    while (Paint.MenuGame())
    {
        Paint.PlayGame();
    }
    Paint.quitSDL(window, renderer);
    return 0;
}