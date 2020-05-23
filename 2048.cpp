#include "Game.h"
#include "window.h"
#include <iostream>
using namespace std;


int main()
{
    int n;
    cout<<"Please Input Size of Game:"<<endl;
    cin>>n;
    Game game(n);
    initialize();
    do {
        game.draw();
        game.processInput();
    } while (S_QUIT != game.getStatus());

    shutdown();

    return 0;
}
