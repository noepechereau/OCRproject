#include <stdio.h>
#include <string.h>
#include <time.h>

#include "demo.h"
#include "useful/builtin.h"
#include "NeuralNetworks/DemoNeuralNetwork.h"
#include "SudokuSolver/sudoku.h"

int main()
{
    char choice[50];
    printf("0 - Image demonstration\n");
    printf("1 - XOR demonstration\n");
    printf("2 - Sudoku solver demonstration\n");
    Console_ReadString(choice, "Waiting for a demonstration choice : ", 99);

    if (!strcmp(choice,"0"))
    {
        ImageDemo();
    }
        
    if (!strcmp(choice,"1"))
    {
        DemoNeural();
    }
    
    if (!strcmp(choice,"2"))
    {
        DemoSolver();
    }

	return 0;
}


