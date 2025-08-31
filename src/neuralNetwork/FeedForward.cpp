#include "../../include/utils/math.hpp"
#include "../../include/Network.hpp"

/*
a series of matrix multiplications to move from input layer and through the 
hidden layers 
*/
void Network::feedForward() {
    Matrix *a;  // Matrix of neurons
    Matrix *b;  // Matrix of weights to the left of the layer
    Matrix *c;  // Matrix of neurons to the right = a * b
    
    for (int i = 0; i < (this->topologySize - 1); i++) {
        a = this->getNeuronMatrix(i);
        b = this->getWeightMatrix(i);
        c = new Matrix(
                    a->getNumRows(),
                    b->getNumCols(),
                    false
                    ); 
        if (i != 0) {
            a = this->getActivatedNeuronMatrix(i); 
        }

        utils::Math::multiplyMatrix(a, b, c);
        for (int c_index = 0; c_index < c->getNumCols(); c_index++) {  // loop columnwise
            this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index) + this->bias);
        }

        // delete pointers!!!
        delete a;
        delete b;
        delete c;
    }
    
}