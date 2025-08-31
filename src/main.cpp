#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <ostream>
#include <time.h>

#include "../include/json.hpp"
using json = nlohmann::json;

#include "../include/utils/math.hpp"
#include "../include/Neuron.hpp"
#include "../include/Layer.hpp"
#include "../include/Matrix.hpp"
#include "../include/Network.hpp"

void printSyntax();

int main(int argc, char **argv) {

    /**
     * Testing config.json file
     */
    if (argc != 2) {
        printSyntax();
        exit(-1);
    }
    
    std::ifstream configFile(argv[1]);
    std::string str((std::istreambuf_iterator<char>(configFile)), 
                std::istreambuf_iterator<char>());
    auto config = json::parse(str);

    double learningRate = config["learningRate"];
    double momentum = config["momentum"];
    double bias = config["bias"];

    std::string trainingFile = config["trainingData"];
    std::string label = config["labelData"];

    std::vector<int> topology = config["topology"];
    for (int i = 0; i < topology.size(); i++) {
        std::cout << topology.at(i) << std::endl;
    }
    Network *n = new Network(topology, 2, 3, 1, bias, learningRate, momentum);
    // for (int i = 0; i < 1000; i++) {
    //     std::cout << "Training run " << (i+1) << std::endl;
    //     n->train(input,
    //              target,
    //              bias, 
    //              learningRate, 
    //              momentum
    //             );
    //     std::cout << "Error: " << n->error << std::endl;
    // }
    

    // testing
    // Neuron *n = new Neuron(0.9);
    // std::cout <<"Val: " << n->getVal() << std::endl;
    // std::cout <<"Activated Val: " << n->getActivatedVal() << std::endl;
    // std::cout <<"Derived Val: " << n->getDerivedVal() << std::endl;
    // Matrix *m = new Matrix(3, 2, true);
    // m->print();
    // std::cout << "=================================================" << std::endl;
    // Matrix *mT = m->transpose();
    // mT->print();
    // std::vector<int> topology;
    // topology.push_back(3);
    // topology.push_back(2);
    // topology.push_back(3);

    // std::vector<double> input;
    // input.push_back(1.0);
    // input.push_back(0.0);
    // input.push_back(1.0);

    // Network *n = new Network(topology);
    // n->setCurrentInput(input);
    // n->print();

    // for (int i = 0; i < 10000; i++) {
    //     Matrix *a = new Matrix(100, 100, true);
    //     Matrix *b = new Matrix(100, 100, true);
    //     Matrix *c = new Matrix(a->getNumCols(), b->getNumRows(), false);
    //     std::cout << "Multiplying matrix at index" << i << std::endl;
    //     utils::Math::multiplyMatrix(a, b, c);
    // }

    // std::vector<double> input;
    // input.push_back(0.2);
    // input.push_back(0.5);
    // input.push_back(0.1);

    // std::vector<double> target;
    // target.push_back(0.2);
    // target.push_back(0.5);
    // target.push_back(0.1);

    // double learningRate = 0.05;
    // double momentum = 1;
    // double bias = 1;

    // std::vector<int> topology;
    // topology.push_back(3);  // input layer

    // // hidden layer(s)
    // // topology.push_back(2);
    // topology.push_back(33);
    // topology.push_back(33);
    // topology.push_back(3);
    // // topology.push_back(12);
    
    // topology.push_back(3);  // output layer

    // Network *n = new Network(
    //     topology,  // rest of the params are defaults but can be set
    //     2, 
    //     3, 
    //     1, 
    //     1, 
    //     0.05, 
    //     1
    // );

    // for (int i = 0; i < 1000; i++) {
    //     std::cout << "Training run " << (i+1) << std::endl;
    //     n->train(input,
    //              target,
    //              bias, 
    //              learningRate, 
    //              momentum
    //             );
    //     std::cout << "Error: " << n->error << std::endl;
    // }

    return 0;
}

void printSyntax() {
    std::cout << "Syntax:" << std::endl;
    std::cout << "./starry <<configFile>>" << std::endl;
}