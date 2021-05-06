#include "dynamic_array.h"
#include <iostream>

class DataContainer {
public:
  DataContainer() = default;

private:
};

void print_int_array(const ds::dynamic_array<int> &arr) {
  for (int i = 0; i < arr.size(); ++i)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {
  std::cout << "Testing dynamic array!" << std::endl;

  // TODO: test other constructors
  // ds::dynamic_array<int> arr2(10, 1);
  // copy constructor vs rvalue?

  // TODO: test dynamic array of more complex types
  // ds::dynamic_array<DataContainer> test;

  ds::dynamic_array<int> arr;

  std::cout << "Testing push_back" << std::endl;
  for (int i = 1; i < 8; ++i) {
    arr.push_back(i);
  }
  print_int_array(arr);
  std::cout << "EXPECTED: 1 2 3 4 5 6 7" << std::endl;

  std::cout << "Testing erase" << std::endl;
  arr.erase(1);
  print_int_array(arr);
  std::cout << "EXPECTED: 1 3 4 5 6 7" << std::endl;

  std::cout << "Testing const array" << std::endl;
  const ds::dynamic_array<int> const_arr(arr);
  print_int_array(const_arr);

  std::cout << "Testing copy assignment" << std::endl;
  ds::dynamic_array<int> arr2 = arr;
  print_int_array(arr2);

  std::cout << "Testing resizing" << std::endl;
  std::cout << "Before: (" << arr.size() << ", " << arr.capacity() << ")\n";
  arr.resize(2);
  std::cout << "After: (" << arr.size() << ", " << arr.capacity() << ")\n";

  std::cout << "Testing shrinking" << std::endl;
  std::cout << "Before: (" << arr.size() << ", " << arr.capacity() << ")\n";
  arr.shrink_to_fit();
  std::cout << "After: (" << arr.size() << ", " << arr.capacity() << ")\n";

  return 0;
}
