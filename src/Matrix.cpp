#include "../include/Matrix.hpp"


Matrix::Matrix(int numRows, int numCols, bool isRandom) {
    this->numRows = numRows;
    this->numCols = numCols;

    for (int i = 0; i < numRows; i++) {
        std::vector<double> colValues;
        for (int j = 0; j < numCols; j++) {
            double r = 0.0;
            if (isRandom) {
                r = this->generateRandomNumber();
            }
            colValues.push_back(r);
        }
        this->values.push_back(colValues);
    }
}

// need to delete matrix after use otherwise the memory grows with each use because pointers
// are not being deleted in transpose() and copy() functions
Matrix *Matrix::transpose() {
    Matrix *m = new Matrix(this->numCols, this->numRows, false);
    for (int i = 0; i < this->numRows; i++) {
        for (int j = 0; j < this->numCols; j++) {
            m->setValue(j, i, this->getValue(i, j));
        }
    }
    return m;
}

Matrix *Matrix::copy() {
    Matrix *m = new Matrix(this->numRows, this->numCols, false);
    for (int i = 0; i < this->numRows; i++) {
        for (int j = 0; j < this->numCols; j++) {
            m->setValue(i, j, this->getValue(i, j));
        }
    }
    return m;
}

// generate small random numbers for weight matrix
double Matrix::generateRandomNumber() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<double> dist(-0.0001, 0.0001);
    return dist(gen);
}

void Matrix::print() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(15) << this->values.at(i).at(j);
        }
        std::cout << std::endl;
    }
}