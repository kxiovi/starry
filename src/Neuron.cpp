#include "../include/Neuron.hpp"  

// constructor
Neuron::Neuron(double val) {
    this->setVal(val);
}

Neuron::Neuron(double val, int activationType) {
    this->setVal(val);
    this->activationType = activationType;
}

// setter
void Neuron::setVal(double val) {
    this->val = val;
    activate();
    derive();
}

// default: sigmoid
void Neuron::activate() {
    if (activationType == TANH) {
        this->activatedVal = tanh(this->val);
    } else if (activationType == RELU) {
        if (this->val > 0) {
            this->activatedVal = this->val;
        } else {
            this->activatedVal = 0;
        }
    } else if (activationType == SIGM) {
        this->activatedVal = 1 / (1 + exp(-this->val));
    } else {
        this->activatedVal = 1 / (1 + exp(-this->val));
    }
}

void Neuron::derive() {
    if (activationType == TANH) {
        this->derivedVal = (1.0 - (this->activatedVal * this->activatedVal));
    } else if (activationType == RELU) {
        if (this->val > 0) {
            this->derivedVal = 1;
        } else {
            this->derivedVal = 0;
        }
    } else if (activationType == SIGM) {
        this->derivedVal = (this->activatedVal * (1 - this->activatedVal));
    } else {
        this->derivedVal = (this->activatedVal * (1 - this->activatedVal));
    }
}
