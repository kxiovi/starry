#pragma once 

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>

#include "Matrix.hpp"
#include "Layer.hpp"
#include "json.hpp"

#define COST_MSE 1

// neural network class
class Network
{
public:
    int topologySize;
    int hiddenActivationType = RELU;
    int outputActivationType = SIGM;
    int costFunctionType = COST_MSE;
    double bias = 1;
    double error = 0;
    double momentum;
    double learningRate;
    std::vector<int> topology;  // each index in the topology vector corresponds to the Layer's index
    std::vector<Layer*> layers;  // 0 = input layer, 1 = hidden layer, n-1 = output layer
    std::vector<Matrix*> weightMatrices;  // num of weightMatrices = # layers - 1 (each contains a pair of layers)
    std::vector<Matrix*> gradientMatrices;  // direction of a weight
    std::vector<double> input;
    std::vector<double> target;  // for learning
    std::vector<double> errors;  // holds error values
    std::vector<double> derivedErrors;  // holds derivatives for the error values

    Network(std::vector<int> topology, 
        double bias = 1, 
        double learningRate = 0.05, 
        double momentum = 1
    );

    Network(std::vector<int> topology, 
        int hiddenActivationType, 
        int outputActivationType, 
        int costFunctionType, 
        double bias = 1, 
        double learningRate = 0.05, 
        double momentum = 1
    );

    void print();
    void feedForward();
    void backPropagation();
    void saveWeights(std::string file);
    void train(std::vector<double> input, 
        std::vector<double> target, 
        double bias, 
        double learningRate, 
        double momentum
    );
    
    void setErrors();
    void setCurrentInput(std::vector<double> input);
    void setCurrentTarget(std::vector<double> target) { this->target = target; };
    void setNeuronValue(int indexLayer, int indexNeuron, double v) { this->layers.at(indexLayer)->setVal(indexNeuron, v); }

    Matrix *getNeuronMatrix(int index) { return this->layers.at(index)->matrixifyVals(); };
    Matrix *getActivatedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyActivatedVals(); };
    Matrix *getDerivedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyDerivedVals(); };
    Matrix *getWeightMatrix(int index) { return new Matrix(*this->weightMatrices.at(index)); };
    std::vector<double> getActivatedVals(int index) { return this->layers.at(index)->getActivatedVals(); };

private:
    
    
    void setErrorMSE();
};