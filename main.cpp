#include "App.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;


int main()
{

    if (App::Singleton().init("Box2D Testing", SCREEN_WIDTH, SCREEN_HEIGHT, false))
    { 
        App::Singleton().Run();
    }
    
    return 0;
}