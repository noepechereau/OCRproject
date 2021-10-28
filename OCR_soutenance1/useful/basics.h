#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED

#include <stdbool.h>
#include "../struct/pixel.h"
#include <SDL2/SDL.h>

void Console_ReadString(char *var, char* message, int size);
bool FileExist(char* path);
void PauseSDL();


#endif // BASICS_H_INCLUDED
