#include "../../include/Network.hpp"

void Network::train(std::vector<double> input, 
        std::vector<double> target, 
        double bias, 
        double learningRate, 
        double momentum
) {
    this->setCurrentInput(input);
    this->setCurrentTarget(target);
    this->bias = bias;
    this->learningRate = learningRate;
    this->momentum = momentum;

    this->feedForward();
    this->setErrors();
    this->backPropagation();

}