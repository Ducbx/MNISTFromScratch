url="http://yann.lecun.com/exdb/mnist/"
mkdir "./dataset/"

for file in "train-images-idx3-ubyte.gz" "train-labels-idx1-ubyte.gz" "t10k-images-idx3-ubyte.gz" "t10k-labels-idx1-ubyte.gz"
do
    echo "${url}${file}"
    curl "${url}${file}" -o "./dataset/${file}"
    gzip -d "./dataset/${file}"
done