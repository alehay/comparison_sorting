#ifndef __MATRIX__HPP__
#define __MATRIX__HPP__

#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

namespace edu {

class base_matrix {
public:
  virtual void rand_fill(std::int32_t rdn_min, std::int32_t rnd_max) = 0;
  virtual void print(std::ostream &stream) const = 0;

  virtual ~base_matrix() = default;
};

template <typename T, typename Alloc = std::allocator<T>>
class matrix : public base_matrix {
  std::vector<std::vector<T>> storage;

public:

/**
 * @brief Construct a new matrix object
 * 
 * @param num_col   the width of the matrix
 * @param num_row   
 * @param rand_min  the minimum possible random number when filling the matrix
 * @param rand_max the maximum possible random number when filling the matrix
 */
  matrix(std::size_t num_col, std::size_t num_row, std::int32_t rand_min, std::int32_t rand_max  ) {
    
    storage.reserve(num_row);
    for (; num_row > 0; --num_row) {
      std::vector<T> row;
      for (size_t i = 0; i < num_col; i++)
      {
        row.emplace_back( generateRandom(rand_min, rand_max));
      }
      storage.emplace_back(std::move(row));
      
    }
  }

  matrix(std::size_t num_col, std::size_t num_row, T el) {
    std::vector<T> tmp(num_col, el);
    storage.reserve(num_row);
    for (; num_row > 0; --num_row) {
      storage.push_back(tmp);
    }
  }

  matrix(matrix<T>const & mat)  {
    storage = mat.storage;

  }

  void rand_fill(std::int32_t rdn_min, std::int32_t rnd_max) override {
    for (auto &row : storage) {
      for (auto &el : row) {
        el = generateRandom(rdn_min, rnd_max);
      }
    }
  }

  auto get_iterator() {
    return (storage[0].begin());
  }


  T generateRandom(std::int32_t min, std::int32_t  max) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    if constexpr (std::is_integral<T>::value) {
      std::uniform_int_distribution<T> dis(min, max);
      return dis(gen);
    } else {
      std::uniform_real_distribution<T> dis(min, max);
      return dis(gen);
    }
  }

  std::size_t get_row_count() const noexcept { return storage.size(); }

  std::vector<T>& get_row(std::size_t ind) {
    return storage[ind];
  }  

  std::size_t get_row_size() const noexcept {
    if (storage.empty()) {
      return 0;
    }
    storage[0].size();
  }

  void print(std::ostream &stream) const override {
    for (const auto &row : storage) {
      for (const auto &row_el : row) {
        stream << row_el << " ";
      }
      stream << "\n";
    }
    stream << std::endl;
  }

  template <typename U, typename V>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const matrix<U, V> &mat);
};

template <typename T, typename Alloc>
std::ostream &operator<<(std::ostream &stream, const matrix<T, Alloc> &mat) {
  for (const auto &row : mat.storage) {
    for (const auto &row_el : row) {
      stream << row_el << " ";
    }
    stream << "\n";
  }
  stream << std::endl;

  return stream;
}

std::ostream &operator<<(std::ostream &stream, const base_matrix &mat) {
  mat.print(stream);
  return stream;
}




} // namespace edu

#endif