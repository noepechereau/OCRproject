#include"builtin.h"
#ifndef FORWARD_PROP_H
#define FORWARD_PROP_H

void updateNode(NeuralNetwork* network, size_t i);
void forwardProp(NeuralNetwork* network);

#endif
