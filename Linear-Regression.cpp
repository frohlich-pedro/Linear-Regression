#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(void) {
  auto mean = [&](vector<double>& data) -> double {
    if (data.empty()) {
      throw runtime_error("ERROR: empty vector");
    }
    
    return accumulate(data.begin(), data.end(), 0.0) / data.size();
  };

  auto variance = [&](vector<double>& data) -> double {
    if (data.empty()) {
      throw runtime_error("ERROR: empty vector");
    }

    double sum = 0;

    for (auto& i : data) {
      sum += (i - mean(data)) * (i - mean(data));
    }

    return sum / data.size();
  };

  auto covariance = [&](vector<double>& x, vector<double>& y) -> double {
    if (x.empty() || y.empty()) {
      throw runtime_error("ERROR: empty vector");
    }

    double sum = 0;

    for (int i = 0; i < x.size(); i++) {
      sum += (x[i] - mean(x)) * (y[i] - mean(y));
    }

    return sum / x.size();
  };

  auto linear_regression = [&](vector<double>& x, vector<double>& y) -> pair<double, double> {
    if (x.empty() || y.empty()) {
      throw runtime_error("ERROR: empty vector");
    }
    double b1 = covariance(x, y) / variance(x);
    double b0 = mean(y) - b1 * mean(x);

    return {b0, b1};
  };

  vector<double> x = {1,2,3,4,5};
  vector<double> y = {0,2,4,6,8};

  try {
    auto [b0, b1] = linear_regression(x, y);
    cout << b0 << ", " << b1 << endl;
  } catch(const runtime_error& error) {
    cerr << error.what() << endl;
  }
  
  return 0;
}
