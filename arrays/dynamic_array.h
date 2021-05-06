#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <cstddef>
#include <memory>

namespace ds {

template <typename T> class dynamic_array {
public:
  dynamic_array() = default; // what does this do?

  explicit dynamic_array(std::size_t size)
      : capacity_(size), data_(new T[size]) {}

  dynamic_array(const dynamic_array<T> &other)
      : size_(other.size_), capacity_(other.capacity_),
        data_(new T[capacity_]) {
    for (int i = 0; i < other.size(); ++i) {
      data_[i] = other[i];
    }
  }

  dynamic_array(dynamic_array<T> &&other)
      : size_(std::move(other.size_)), capacity_(std::move(other.capacity_)),
        data_(std::move(other.data_)) {
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~dynamic_array() { delete[] data_; }

  dynamic_array<T> &operator=(const dynamic_array<T> &other) {
    dynamic_array<T> copy{other};
    std::swap(size_, copy.size_);
    std::swap(capacity_, copy.capacity_);
    std::swap(data_, copy.data_);
    return *this;
  }

  dynamic_array<T> &operator=(dynamic_array<T> &&other) {
    dynamic_array<T> copy{std::move(other)};
    std::swap(size_, copy.size_);
    std::swap(capacity_, copy.capacity_);
    std::swap(data_, copy.data_);
    return *this;
  }

  void push_back(T elem) {
    if (size_ + 1 == capacity_) {
      resize(growth_rate);
    }
    data_[size_++] = elem;
  }

  void emplace_back() {} // TODO

  void erase(std::size_t pos) { // assume pos is valid
    for (int i = pos + 1; i < size_; ++i) {
      data_[i - 1] = data_[i];
    }
    --size_;

    // we could test to see if we should shrink but STL containers never shrink
    // unless explicitly requested to by shrink_to_fit()
  }

  T &operator[](std::size_t pos) { return data_[pos]; }
  const T &operator[](std::size_t pos) const { return data_[pos]; }

  void resize(double ratio) {
    capacity_ *= ratio;
    T *new_data{new T[capacity_]};
    for (int i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }

  void shrink_to_fit() {
    capacity_ = size_;
    T *new_data{new T[capacity_]};
    for (int i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }

  bool empty() const { return size_ == 0; }
  std::size_t capacity() const { return capacity_; }
  std::size_t size() const { return size_; }

private:
  const static std::size_t starting_size{8};
  constexpr static double growth_rate{2}; // 1.5 (or golden ratio) may be better

  std::size_t size_{0};
  std::size_t capacity_{starting_size};

  T *data_ = new T[starting_size]; // TODO: use unique_ptr instead
};
} // namespace ds

#endif // DYNAMIC_ARRAY_H_
