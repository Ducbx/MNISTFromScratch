cmake_minimum_required(VERSION 3.0.0)
project(MNISTFromScratch)

include_directories(include)

add_executable(MNISTFromScratch 
    "src/main.cpp"
    "src/loadDataset.cpp"
    "src/NeuralNetwork.cpp"
    "src/LinearLayer.cpp"
)