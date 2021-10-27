#ifndef BUILTIN_H_INCLUDED
#define BUILTIN_H_INCLUDED

#include <stdbool.h>
#include "../type/pixel.h"

void DisplayError(char* message);
void Console_ReadString(char *var, char* message, int size);
bool FileExist(char* path);
void PauseSDL();

#endif // BUILTIN_H_INCLUDED
