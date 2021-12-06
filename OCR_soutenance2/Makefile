CC = @gcc
CFLAGS = -Wall -Wextra -g -ldl -lm

SRC = useful/basics.c image_system/image_manipulation.c image_system/color_system.c image_system/image_system.c NeuralNetwork/builtin.c NeuralNetwork/backprop.c NeuralNetwork/forwardprop.c NeuralNetwork/learning.c sudoku_detection/grille_detection.c rotation/rotation.c SudokuSolver/sudoku.c

LINKERFLAGS = -lSDL2 -lSDL2_image

OBJ= $(SRC:.c=.o)

all: compile exec

compile: $(OBJ)
	@echo "Compiled"

exec:
	@gcc $(OBJ) $(CFLAGS) $(LINKERFLAGS)
	@echo "a.out generated"

clean :
	@rm -f *.o
	@rm -f $(OBJ)
	@rm -f a.out
	@echo "Cleaned"

