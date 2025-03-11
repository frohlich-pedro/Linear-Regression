#include <iostream>
#include <vector>
#include <numeric>

std::pair<double, double> linearRegression(std::vector<double>& x, std::vector<double>& y);

int main(void) {
  std::vector<double> x = {1,2,3,4,5};
  std::vector<double> y = {0,2,4,6,8};

  try {
    auto [b0, b1] = linearRegression(x, y);
    std::cout << b0 << ", " << b1 << std::endl;
  } catch (const runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}

std::pair<double, double> linearRegression(std::vector<double>& x, std::vector<double>& y) {
  auto mean = [&](std::vector<double>& data) -> double {
    if (data.empty()) {
      throw std::runtime_error("ERROR: empty vector");
    }
    
    return accumulate(data.begin(), data.end(), 0.0) / data.size();
  };

  auto variance = [&](std::vector<double>& data) -> double {
    if (data.empty()) {
      throw std::runtime_error("ERROR: empty vector");
    }

    double sum = 0;
    for (auto& i : data) {
      sum += (i - mean(data)) * (i - mean(data));
    }

    return sum / data.size();
  };

  auto covariance = [&](std::vector<double>& x, std::vector<double>& y) -> double {
    if (x.empty() || y.empty()) {
      throw std::runtime_error("ERROR: empty vector");
    }

    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
      sum += (x[i] - mean(x)) * (y[i] - mean(y));
    }

    return sum / x.size();
  };

  if (x.empty() || y.empty()) {
    throw std::runtime_error("ERROR: empty vector");
  }
  
  double b1 = covariance(x, y) / variance(x);
  double b0 = mean(y) - b1 * mean(x);

  return {b0, b1};
}
