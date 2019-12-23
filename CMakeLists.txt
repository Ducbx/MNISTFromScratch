cmake_minimum_required(VERSION 3.0.0)
project(MNISTFromScratch)

include_directories(include)

add_executable(MNISTFromScratch 
    "src/main.cpp"
    "src/load_dataset.cpp"
    "src/NN.cpp"
    "src/LinearLayer.cpp"
)