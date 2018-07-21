This directory just contains some code to do some quick simulations and details
of how I did them.

In this directory is also some small snippets of MNIST data that I used, but
you'll need to gunzip it.

So far there are two experiments:

1. Estimate the runtime of a ReLU layer: relu.cpp

For this you need Armadillo installed.  You can just compile as

g++ -o relu relu.cpp -O3 -larmadillo

and you can run it and it should print how long it took, with no need for any
arguments.  This simulates a forward pass of 64 points through a ReLU layer with
784 input dimensions, a width of 500, and an output dimension of 500.  The data
used is uniform random but it shouldn't make a difference either way.

If you use OpenBLAS note that you can control the number of threads used with
OMP_NUM_THREADS (the OpenMP environment variable) when you run.

2. Estimate the runtime of maximum inner product search.

For this one we don't need any special code, we just need a working executable
of 'mlpack_fastmks' out of mlpack.  Assuming that is installed, we can use the
datasets I have floating around in this directory:

# Compute MIPS with 64 MNIST input points, searching 500 w_i vectors.
mlpack_fastmks -q mnist_64.csv -r mnist_500.csv -v -K linear -k 1

# Compute MIPS with 64 MNIST input points, searching 5000 w_i vectors.
mlpack_fastmks -q mnist_64.csv -r mnist_5000.csv -v -K linear -k 1

Note a couple things for these experiments:

  - They don't use the MIPS-optimized cone tree and could be slightly slower.
  - They are singlethreaded.
  - They assume that the w_i that are found come from the same distribution as
    the input vectors (very unlikely to be true I think), and the dependence of
    runtime on distribution is strong.  There is also rand_500.csv and
    rand_5000.csv which are unit random vectors in 784d.
  - The input dimensionality is high, which typically causes slower search.
  - In fact if you look at the number of base cases, barely any prunes are
    happening at all with this data.
