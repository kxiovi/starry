#pragma once

#include <iostream>
#include <math.h>

// activation types
#define TANH 1
#define RELU 2
#define SIGM 3

class Neuron 
{
public:

    // Neuron construction must have a value
    Neuron(double val);
    Neuron(double val, int activationType);

    // activation functions (default: sigmoid fxn)
    void activate();

    // derivative of activation functions
    void derive();

    // setter
    void setVal(double v);

    // getters
    double getVal() { return this->val;}
    double getActivatedVal() { return this->activatedVal;}
    double getDerivedVal() { return this->derivedVal;}


private:
    double val;
    
    double activatedVal;  // normalize
    double derivedVal;  // derivative of activated value

    int activationType;

};
