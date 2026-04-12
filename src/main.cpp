#include <iostream>

//External Libraries
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) 
    {
        std::cerr << "SDL3 failed to intialize: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "SDL3 has intialized!" << std::endl;

    SDL_Quit();
    return EXIT_SUCCESS;
}
