#pragma once

#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"

class Layer 
{
public:
    // constructor
    Layer(int size);

    Layer(int size, int activationType);

    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();

    void setVal(int i, double v);  // i = index, v = value
    void setNeurons(std::vector<Neuron *> neurons) { this->neurons = neurons; };

    std::vector<Neuron *> getNeurons() { return this->neurons; };
    std::vector<double> getActivatedVals();

private:
    int size;  // num of neurons in layer
    std::vector<Neuron*> neurons;
};
