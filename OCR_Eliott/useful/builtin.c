#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <io.h>
#else
#include <SDL2/SDL.h>
#include <stdbool.h>
#	include <unistd.h>
#endif
#include <string.h>

void PauseSDL()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

void DisplayError(char* message)
{
    printf("%s",message);
    exit(1);
}

bool FileExist(char* path)
{
    if(access(path, 0 ))
    {
        printf("'%s' doesn't exist !", path);
        return false;
    }
    return true;
}

void Console_ReadString(char *var, char* message, int size)
{
    printf("%s",message);
    char *start = NULL;

    if (fgets(var, size, stdin) != NULL)
    {
        start = strchr(var, '\n');
        if (start != NULL)
        {
            *start = '\0';
        }
    }
}

size_t max_size(size_t a, size_t b)
{
    if (a >= b)
        return a;
    return b;
}


