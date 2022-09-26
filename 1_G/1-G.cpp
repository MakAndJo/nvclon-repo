#include <cmath>
#include <iomanip>
#include <iostream>
std::pair<long double, int> Simplify(long double x) {
  if (x > 1) {
    return {Simplify(x / 10).first, Simplify(x / 10).second + 1};
  }
  if (x <= 0.1) {
    return {Simplify(x * 10).first, Simplify(x * 10).second - 1};
  }
  return {x, 0};
}
long double FindGeoAvgOfElements(std::pair<long double, int>* prefix, int l,
                                 int r) {
  std::pair<long double, int> temp_pair =
      Simplify(prefix[r].first / prefix[l - 1].first);
  std::pair<long double, int> multiplication = {
      temp_pair.first,
      temp_pair.second + prefix[r].second - prefix[l - 1].second};
  long double power = static_cast<long double>(1) / (r - l + 1);
  return std::pow(multiplication.first, power) *
         std::pow(10, multiplication.second * power);
}
int main() {
  std::cout.precision(16);
  int n;
  std::pair<long double, int> *prefix = new std::pair<long double, int>[300001];
  std::cin >> n;
  prefix[0] = {1, 0};
  for (int i = 0; i < n; i++) {
    long double temp;
    std::cin >> temp;
    std::pair<long double, int> temp_pair = Simplify(prefix[i].first * temp);
    prefix[i + 1].first = temp_pair.first;
    prefix[i + 1].second = temp_pair.second + prefix[i].second;
  }
  int q;
  std::cin >> q;
  for (int k = 0; k < q; k++) {
    int i, j;
    std::cin >> i >> j;
    std::cout << FindGeoAvgOfElements(prefix, i + 1, j + 1) << "\n";
  }
  delete[] prefix;
  return 0;
}
