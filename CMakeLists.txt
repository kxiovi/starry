cmake_minimum_required(VERSION 3.20)
project(starry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread")

add_executable(
    starry 
    src/train.cpp
    src/Neuron.cpp
    src/Matrix.cpp
    src/Layer.cpp
    src/neuralNetwork/Network.cpp
    src/neuralNetwork/SetErrors.cpp
    src/neuralNetwork/BackPropagation.cpp   
    src/neuralNetwork/FeedForward.cpp
    src/neuralNetwork/Train.cpp
    src/utils/math.cpp
    src/utils/misc.cpp
    )