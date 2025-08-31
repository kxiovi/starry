#include "../../include/Network.hpp"

using json = nlohmann::json;

// constructors 
Network::Network(
    std::vector<int> topology, 
    double bias, 
    double learningRate, 
    double momentum
) {
    this->topology = topology;
    this->topologySize = topology.size();
    this->bias = bias;
    this->learningRate = learningRate;
    this->momentum = momentum;

    for (int i = 0; i < topologySize; i++) {
        Layer *l;
        if (i > 0 && i < (topologySize - 1)) {
            // we are in hidden layer
            l  = new Layer(topology.at(i), this->hiddenActivationType);
            this->layers.push_back(l);
        } else if (i == (topologySize - 1)) {
            l = new Layer(topology.at(i), this->outputActivationType);
            this->layers.push_back(l);
        } else {
            // input layer
            l = new Layer(topology.at(i));
            this->layers.push_back(l);
        }
    }

    for (int i = 0; i < topologySize - 1; i++) {
        Matrix *m = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(m);
    }

    // set errors to 0.0
    for (int i = 0; i < topology.at((topologySize - 1)); i++) {
        errors.push_back(0.0);
        derivedErrors.push_back(0.0);
    }

    this->error = 0.0;  // set final error to 0.0
}

Network::Network(
    std::vector<int> topology, 
    int hiddenActivationType, 
    int outputActivationType, 
    int costFunctionType,
    double bias, 
    double learningRate, 
    double momentum
) {
    this->topology = topology;
    this->topologySize = topology.size();
    this->bias = bias;
    this->learningRate = learningRate;
    this->momentum = momentum;
    this->hiddenActivationType = hiddenActivationType;
    this->outputActivationType = outputActivationType;
    this->costFunctionType = costFunctionType;

    for (int i = 0; i < topologySize; i++) {
        Layer *l;
        if (i > 0 && i < (topologySize - 1)) {
            // we are in hidden layer
            l  = new Layer(topology.at(i), this->hiddenActivationType);
            this->layers.push_back(l);
        } else if (i == (topologySize - 1)) {
            l = new Layer(topology.at(i), this->outputActivationType);
            this->layers.push_back(l);
        } else {
            // input layer
            l = new Layer(topology.at(i));
            this->layers.push_back(l);
        }
    }

    for (int i = 0; i < topologySize - 1; i++) {
        Matrix *m = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(m);
    }

    // set errors to 0.0
    for (int i = 0; i < topology.at((topologySize - 1)); i++) {
        errors.push_back(0.0);
        derivedErrors.push_back(0.0);
    }

    this->error = 0.0;  // set final error to 0.0
}

void Network::print() {
    for (int i = 0; i < this->layers.size(); i++) {
        std::cout << "LAYER: " << i << std::endl;
        if (i==0) {
            Matrix *m = this->layers.at(i)->matrixifyVals();
            m->print();
        } else {
            Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
            m->print();
        }
    }
}

void Network::setCurrentInput(std::vector<double> input) {
    this->input = input;
    for (int i = 0; i < input.size(); i++) {
        this->layers.at(0)->setVal(i, input.at(i)); // set input values for the inital layer
    }
    
}

void Network::saveWeights(std::string file) {
    json j = {};
    std::vector<std::vector<std::vector<double>>> weightSet;
    for (int i = 0; i < this->weightMatrices.size(); i++) {
        weightSet.push_back(this->weightMatrices.at(i)->getValues());
    }
    j["weights"] = weightSet;
    std::ofstream o(file);
    o << std::setw(4) << j << std::endl;
}

