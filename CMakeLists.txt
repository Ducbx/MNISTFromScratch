cmake_minimum_required(VERSION 3.0.0)
project(MNISTFromScratch)

find_package(OpenMP)
include_directories(include)

set(CMAKE_CXX_FLAGS "-ffast-math")

add_executable(MNISTFromScratch 
    "src/main.cpp"
    "src/loadDataset.cpp"
    "src/NeuralNetwork.cpp"
    "src/matrix.cpp"
    "src/training.cpp"
)

target_link_libraries(MNISTFromScratch OpenMP::OpenMP_CXX)