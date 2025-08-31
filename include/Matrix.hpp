#pragma once

#include <iostream> 
#include <vector>
#include <random>
#include <iomanip>

class Matrix 
{
public:
    // constructor
    Matrix(int numRows, int numCols, bool isRandom);
    
    // transpose matrix fxn
    Matrix *transpose();

    // copy matrix
    Matrix *copy();

    // print the values of the matrix
    void print();
    
    // setter
    void setValue(int r, int c, double v) { this->values.at(r).at(c) = v; };
    
    // getters
    double getValue(int r, int c) { return this->values.at(r).at(c); };
    int getNumRows() { return this->numRows; }
    int getNumCols() { return this->numCols; }
    std::vector<std::vector<double>> getValues() { return this->values; };
    
private:
    int numRows;
    int numCols;
    std::vector <std::vector<double>> values;

    // generate random number fxn
    double generateRandomNumber();

};