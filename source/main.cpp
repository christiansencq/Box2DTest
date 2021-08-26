#include "App.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
    if (App::Singleton().Init("Box2D Testing", SCREEN_WIDTH, SCREEN_HEIGHT, false))
    { 
        App::Singleton().Run();
    }
    return 0;
}
