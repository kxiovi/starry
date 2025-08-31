/*
The loss function is used during training to measure how close the network's 
prediction was the actual answer (smaller value = smaller error). This error value
is used to adjust weights in the network. 
*/

#include <assert.h>

#include "../../include/Network.hpp"

void Network::setErrors() {
    if (this->target.size() == 0) {
        std::cerr << "No target for this neural network. Must have a target." << std::endl;
        assert(false);
    }
    if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size()) {
        std::cerr << "Target size (" << this->target.size() << ") is not the same as output layer size: " << this->layers.at(this->layers.size() - 1)->getNeurons().size() << std::endl;
        for (int i = 0; i < this->target.size(); i++) {
            std::cout << this->target.at(i) << std::endl;
        }
        assert(false);
    }
    switch(costFunctionType) {
        case(COST_MSE): 
            this->setErrorMSE();
            break;
        default: 
            this->setErrorMSE();
            break;
    }
}

void Network::setErrorMSE() {
    int outputLayerIndex = this->layers.size() - 1;
    std::vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();
    this->error = 0.0;
    for (int i = 0; i < target.size(); i++) {
        double t = target.at(i);
        double y = outputNeurons.at(i)->getActivatedVal();
        errors.at(i) = 0.5 * pow(abs((t-y)), 2);
        derivedErrors.at(i) = y-t;  // derivedErrors is a vector
        this->error += errors.at(i);  // this->error = sum of all errors
    }
}