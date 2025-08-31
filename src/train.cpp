/**
 * train the neural network
 * Note: Images used require 3136 input neurons
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <ostream>
#include <time.h>

#include "../include/json.hpp"
using json = nlohmann::json;

#include "../include/utils/math.hpp"
#include "../include/utils/misc.hpp"
#include "../include/Neuron.hpp"
#include "../include/Layer.hpp"
#include "../include/Matrix.hpp"
#include "../include/Network.hpp"


int main(int argc, char **argv) {
    
    std::ifstream configFile(argv[1]);
    std::string str((std::istreambuf_iterator<char>(configFile)), 
                std::istreambuf_iterator<char>());
    auto config = json::parse(str);

    double learningRate = config["learningRate"];
    double momentum = config["momentum"];
    double bias = config["bias"];

    std::string trainingFile = config["trainingData"];
    std::string labelFile = config["labelData"];
    std::string weightsFile = config["weights"];

    int epoch = config["epoch"];

    std::vector<int> topology = config["topology"];
    for (int i = 0; i < topology.size(); i++) {
        std::cout << topology.at(i) << std::endl;
    }
    Network *n = new Network(topology, 2, 3, 1, bias, learningRate, momentum);
    std::vector<std::vector<double>> trainingData = utils::Misc::fetchData(trainingFile);
    std::vector<std::vector<double>> labelData = utils::Misc::fetchData(labelFile);

    std::cout << "Training data size: " << trainingData.size() << std::endl;
    std::cout << "Labels size: " << labelData.size() << std::endl;

    for (int i = 0; i < epoch; i++) {
        for (int tIndex = 0; tIndex < trainingData.size(); tIndex++) {
            std::vector<double> input = trainingData.at(tIndex);
            std::vector<double> target = labelData.at(tIndex);
            n->train(input,
                    target,
                    bias, 
                    learningRate, 
                    momentum
                    );
        }
        
        std::cout << "Error at epoch " << (i+1) << ": " << n->error << std::endl;
        n->saveWeights(weightsFile);
    }

    std::cout << "\nWriting to " << weightsFile << std::endl;
}