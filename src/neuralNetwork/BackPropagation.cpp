/*
feed forward: input layer -> hidden layers -> output layer
back propagation: output -> last hidden layer -> input layer
*/

#include "../../include/utils/math.hpp"
#include "../../include/Network.hpp"

void Network::backPropagation() {
    std::vector<Matrix*> newWeights;
    Matrix *deltaWeights;
    Matrix *gradients;  // should be same size as deltaWeights matrix; this is G_p
    Matrix *derivedValues;
    Matrix *gradientsTransposed;
    Matrix *zActivatedVals;
    Matrix *tempNewWeights;
    Matrix *pGradients;
    Matrix *transposedPWeights;
    Matrix *hiddenDerived;
    Matrix *transposedHidden;

    // first: output -> last hidden layer

    // output to the last hidden layer i.e. layer to the right is the output layer
    int indexOutputLayer = this->topology.size() - 1; // get the index by - 1;

    // gradients are approximations of derivatives & are used to dictate the direction
    // of the error function of the network so that weights can be adjusted to minimize error
    gradients = new Matrix(
                    1, 
                    this->topology.at(indexOutputLayer), 
                    false
                );
    
    // create new matrix consisting of derived errors * derived ouput values
    // has 1 row, and num of cols = nums of neurons in output layer
    derivedValues = this->layers.at(indexOutputLayer)->matrixifyDerivedVals();
    for (int i = 0; i < this->topology.at(indexOutputLayer); i++) {
        double e = this->derivedErrors.at(i);
        double y = derivedValues->getValue(0, i);
        double g = e * y;  // g represents the gradient
        gradients->setValue(0, i, g);  // has 1 row, i = col index, value is g
    }
    delete derivedValues;

    // multiply the transpose of the new matrix with the gradient to the output of the left layer
    // G _^T * Z  = deltaWeights
    gradientsTransposed = gradients->transpose();
    zActivatedVals = this->layers.at(indexOutputLayer - 1)->matrixifyActivatedVals();
    deltaWeights = new Matrix(
                        gradientsTransposed->getNumRows(),
                        zActivatedVals->getNumCols(), 
                        false
    );
    ::utils::Math::multiplyMatrix(gradientsTransposed, zActivatedVals, deltaWeights);
    
    // new weights = original_weights - deltaWeights
    tempNewWeights = new Matrix (
        this->topology.at(indexOutputLayer - 1), 
        this->topology.at(indexOutputLayer), 
        false
    );
    for (int r = 0; r < this->topology.at(indexOutputLayer - 1); r++) {
        for (int c = 0; c < this->topology.at(indexOutputLayer); c++) {
            double originalValue = this->weightMatrices.at(indexOutputLayer - 1)->getValue(r,c);
            double deltaValue = deltaWeights->getValue(c, r);
            originalValue *= this->momentum;
            deltaValue *= this->learningRate;
            tempNewWeights->setValue(r, c, (originalValue - deltaValue));
        }
    }
    newWeights.push_back(new Matrix(*tempNewWeights));

    // delete pointers
    delete deltaWeights;
    delete gradientsTransposed;
    delete zActivatedVals;
    delete tempNewWeights;

    // second: last hidden layer -> input layer
    // the previous weight matrix will be index i (b/c they are to the right)
    for (int i = (indexOutputLayer - 1); i > 0; i--) {
        
        // get previous gradients and weights
        pGradients = new Matrix(*gradients);
        delete gradients;
        transposedPWeights = this->weightMatrices.at(i)->transpose();
        gradients = new Matrix (
            pGradients->getNumRows(), 
            transposedPWeights->getNumCols(), 
            false
        );

        // G = (G_p * W_p_^T) * Z'
        ::utils::Math::multiplyMatrix(pGradients, transposedPWeights, gradients);
        hiddenDerived = this->layers.at(i)->matrixifyDerivedVals();
        for (int colCounter = 0; colCounter < hiddenDerived->getNumCols(); colCounter++) {
            double g = gradients->getValue(0, colCounter) * hiddenDerived->getValue(0, colCounter);
            gradients->setValue(0, colCounter, g);
        }
        
        if (i==1) {
            // don't need  activated vals for the layer to the right of input layer
            // because only 1 hidden layer
            zActivatedVals = this->layers.at(0)->matrixifyVals();  
        } else {
            zActivatedVals = this->layers.at(i-1)->matrixifyActivatedVals();
        }
        transposedHidden = zActivatedVals->transpose();
        deltaWeights = new Matrix(
            transposedHidden->getNumRows(), 
            gradients->getNumCols(), 
            false
        );

        // std::cout << "transposedHidden: " << transposedHidden->getNumRows() << ", " << transposedHidden->getNumCols() << std::endl;
        // std::cout << "gradients: " << gradients->getNumRows() << ", " << gradients->getNumCols() << std::endl;
        // std::cout << "deltaWeights: " << deltaWeights->getNumRows() << ", " << deltaWeights->getNumCols() << std::endl;

        ::utils::Math::multiplyMatrix(transposedHidden, gradients, deltaWeights);
        tempNewWeights = new Matrix(
            this->weightMatrices.at(i-1)->getNumRows(),
            this->weightMatrices.at(i-1)->getNumCols(),
            false
        );
        for (int r = 0; r < tempNewWeights->getNumRows(); r++) {
            for (int c = 0; c < tempNewWeights->getNumCols(); c++) {
                double originalValue = this->weightMatrices.at(i-1)->getValue(r, c);
                double deltaValue = deltaWeights->getValue(r, c);
                originalValue *= this->momentum;
                deltaValue *= this->learningRate;
                tempNewWeights->setValue(r, c, (originalValue - deltaValue));
            }
        }
        newWeights.push_back(new Matrix(*tempNewWeights));
        delete pGradients;
        delete transposedHidden;
        delete tempNewWeights;
        delete hiddenDerived;
        delete zActivatedVals;
        delete deltaWeights;
        delete transposedPWeights;
    }

    // delete pointers
    delete gradients;
    for (int i = 0; i < this->weightMatrices.size(); i++) {
        delete this->weightMatrices.at(i);
    }
    this->weightMatrices.clear();

    reverse(newWeights.begin(), newWeights.end());
    for (int i = 0; i < newWeights.size(); i++) {
        this->weightMatrices.push_back(new Matrix(*newWeights.at(i)));
        delete newWeights.at(i);
    }
}