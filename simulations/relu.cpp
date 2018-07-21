#include <cfloat>
#include <armadillo>

using namespace arma;

int main()
{
  // 64 points from a fake MNIST dataset.
  mat input(784, 64, arma::fill::randu);
  mat weightsIn(500, 784, arma::fill::randu); // W == P
  mat weightsOut(500, 500, arma::fill::randu);

  wall_clock w;
  w.tic();
  mat output = weightsOut * arma::clamp(weightsIn * input, 0.0, DBL_MAX);
  double time = w.toc();

  std::cout << "It took " << time << " seconds." << std::endl;
}
