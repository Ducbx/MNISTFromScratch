![GitHub Logo](/images/MNISTHeader.png)

# MNIST From Scratch

In an effort to get more familiar with backpropagation I embarked on a project in which I wrote a neural network, a small linear algebra library, and a simple neural network optimizer from scratch. The neural network is trained on the MNIST dataset. I have implemented the following from scratch:

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
