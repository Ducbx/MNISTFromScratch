![GitHub Logo](/images/MNISTHeader.png)

# MNIST From Scratch

Classifying hand written digits with a neural network from the ground up. In this project I have implemented the following from scratch:

    - Backpropagation algorithm
    - Neural network class
    - Parallelization (with OpenMP, so not entirely from scratch)
    - Necessary linear algebra operations (transpose, matrix multiplication, etc.)
    - Loading dataset from binary distribution

## Features

    - Batch level and dataset-level parallelization with OpenMP
    - Pretty printing of image and evaluation of image by network
    - Zero'ing out of small weights (just an experiment)
    - Script to download dataset (download_dataset.sh)

### Pretty printing output
![example output](/images/example_output.png)
