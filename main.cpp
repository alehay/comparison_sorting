
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

#include "include/cxxopts.hpp"
#include "include/edu_bubble.hpp"
#include "include/edu_heap_sort.hpp"
#include "include/edu_insertion_sort.hpp"
#include "include/edu_quicksort.hpp"
#include "include/edu_selection_sort.hpp"
#include "include/edu_shell_sort.hpp"
#include "include/edu_tournament_sort.hpp"
#include "include/edu_bitwise.hpp"
#include "include/pdqsort.h"
#include "include/matrix.hpp"
#include "include/timer.hpp"

std::mutex global_mutex;

class bSortMeter
{
public:
};

template <typename algorithm, typename container>
class sortMeter
{
private:
  algorithm *alg;
  container cont;
  std::string name;
  Timer t;

  void print_result()
  {
    std::scoped_lock lock(global_mutex);
    std::cout << "name is " << name << "; elapsed mks is "
              << t.elapsedMicrosec() << std::endl;
  }

public:
  sortMeter(algorithm *alg_, container const &cont_, std::string &&name)
      : alg{alg_}, cont(cont_), name{name} {}

  void operator()()
  {
    for (std::size_t it = 0; it < cont.get_row_count(); --it)
    {
      if (std::is_sorted(cont.get_row(it).begin(), cont.get_row(it).end()))
      {
        std::cout << name << "ready sorted!!!!!" << std::endl;
        return;
      }
    }

    t.start();
    for (std::size_t it = 0; it < cont.get_row_count(); --it)
    {
      alg(cont.get_row(it).begin(), cont.get_row(it).end());
    }
    t.stop();
    for (std::size_t it = 0; it < cont.get_row_count(); --it)
    {
      if (!std::is_sorted(cont.get_row(it).begin(), cont.get_row(it).end()))
      {
        std::cout << name << "SORTED FAIL !!!" << std::endl;
        return;
      }
    }
    print_result();
  }
  std::int64_t elapsedMicrosec() const { return t.elapsedMicrosec(); }

  template <typename U, typename V>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const sortMeter<U, V> &meter);
};

template <typename algorithm, typename container>
std::ostream &operator<<(std::ostream &stream,
                         const sortMeter<algorithm, container> &meter)
{
  return stream << std::left << "name is " << meter.name
                << "; sorted element is " << std::setw(20)
                << "; elapsed milliseconds is " << std::setw(10)
                << meter.elapsedMicrosec() << std::endl;
}

int main(int argc, char *argv[])
{
  cxxopts::Options options("example  ./test_sort --width=100  --height=100 -i "
                           "(or -r) --rndMax=-70 --rndMax=70 ");
  // clang-format off
  options.add_options()("h,help", "Print usage")
  ("d,debug", "Enable debugging") // a bool parameter
  ("height", "the height of the matrix", cxxopts::value<std::int32_t>())
  ("width", "the width of the matrix", cxxopts::value<std::int32_t>())
  ("rndMin", "maximum value", cxxopts::value<std::int32_t>())
  ("rndMax", "minimum value", cxxopts::value<std::int32_t>())
  ("i,integer", "Int type param")
  ("r,real", "floating point type param")
  ("p,print", "print matrix if matrix < 20X20" , cxxopts::value<bool>())
  ("f,file", "File name (load values from a file) ", cxxopts::value<std::string>());
  // clang-format on

  auto opt = options.parse(argc, argv);

  if (opt["help"].as<bool>() || argc < 2)
  {
    std::cout << "a test program created as a laboratory work on the subject "
                 "of data structures and algorithms \n";
    std::cout << options.help();
  }

  if (opt["integer"].as<bool>() && opt["real"].as<bool>())
  {
    std::cout
        << "integer keys and real keys are incompatible, please choose one!"
        << std::endl;
    std::exit(1);
  }
  if (!opt["integer"].as<bool>() && !opt["real"].as<bool>())
  {
    std::cout << "please choose one real or integer!" << std::endl;
    std::exit(1);
  }

  std::int32_t rand_max = opt["rndMax"].as<std::int32_t>();
  std::int32_t rand_min = opt["rndMin"].as<std::int32_t>();

  if (rand_max < rand_min)
  {
    std::cout << "rand value incorrect !" << std::endl;
    std::exit(1);
  }

  std::int32_t mat_width = opt["width"].as<std::int32_t>();
  std::int32_t mat_height = opt["height"].as<std::int32_t>();

  if (mat_height * mat_height < 4)
  {
    std::cout << "I can't create a matrix! " << std::endl;
    std::exit(1);
  }

  //  edu::matrix<double> mat_d;
  //  edu::matrix<std::int32_t> mat_i;
  std::unique_ptr<edu::base_matrix> mat;
  std::vector<std::thread> tread_vector;

  if (opt["integer"].as<bool>())
  {
    mat = std::make_unique<edu::matrix<std::int32_t>>(mat_width, mat_height,
                                                      rand_min, rand_max);
  }
  if (opt["real"].as<bool>())
  {
    mat = std::make_unique<edu::matrix<double>>(mat_width, mat_height, rand_min,
                                                rand_max);
  }

  if (opt["p"].as<bool>() && mat_width * mat_height <= 20 * 20)
  {
    mat->print(std::cout);
  }

  edu::matrix<double> *double_mat =
      dynamic_cast<edu::matrix<double> *>(mat.get());

  edu::matrix<std::int32_t> *integer_mat =
      dynamic_cast<edu::matrix<std::int32_t> *>(mat.get());

  //
  if (double_mat)
  {
    // clang-format off
    sortMeter sort_intro(std::sort<decltype(double_mat->get_iterator())>,
                         *double_mat, "introsort libstdc++");
    tread_vector.emplace_back(sort_intro);


    sortMeter sort_heap(
      edu::heap_sort<decltype(double_mat->get_iterator())>, *double_mat,
        "heap_srot");
    tread_vector.emplace_back(sort_heap);

    sortMeter sort_insertion(
      edu::insertion_sort<decltype(double_mat->get_iterator())>, *double_mat,
      "insertion_sort");
    tread_vector.emplace_back(sort_insertion);

    sortMeter sort_quickSort(
      edu::quickSort<decltype(double_mat->get_iterator())>, *double_mat,
      "quickSort");
    tread_vector.emplace_back(sort_quickSort);

    sortMeter sort_selection(
      edu::selection_sort<decltype(double_mat->get_iterator())>, *double_mat,
      "sort_selection");
    tread_vector.emplace_back(sort_selection);

    sortMeter sort_shell(
      edu::shell_sort<decltype(double_mat->get_iterator())>, *double_mat,
      "shell_sort");
    tread_vector.emplace_back(sort_shell);

//    sortMeter bit_sort_int(
//      edu::radix_sort<decltype(double_mat->get_iterator())>, *double_mat,
//      "radix_sort doule");
//      tread_vector.emplace_back(bit_sort_int);
    
    sortMeter pdqsort(
      ::pdqsort<decltype(double_mat->get_iterator())>, *double_mat,
      "PDQD SORT double");
      tread_vector.emplace_back(pdqsort);

  
    //clang-format on
  }

if (integer_mat) {
     // clang-format off

    sortMeter sort_intro(std::sort<decltype(integer_mat->get_iterator())>,
                         *integer_mat, "introsort libstdc++");
    tread_vector.emplace_back(sort_intro);

    sortMeter sort_heap_int(
        edu::heap_sort<decltype(integer_mat->get_iterator())>, *integer_mat,
        "heap_sort_int");
    tread_vector.emplace_back(sort_heap_int);

    sortMeter sort_insertion_int(
        edu::insertion_sort<decltype(integer_mat->get_iterator())>, *integer_mat,
        "insertion_sort_int");
    tread_vector.emplace_back(sort_insertion_int);

    sortMeter sort_quickSort_int(
        edu::quickSort<decltype(integer_mat->get_iterator())>, *integer_mat,
        "quickSort_int");
    tread_vector.emplace_back(sort_quickSort_int);

    sortMeter sort_selection_int(
        edu::selection_sort<decltype(integer_mat->get_iterator())>, *integer_mat,
        "selection_sort_int");
    tread_vector.emplace_back(sort_selection_int);

    sortMeter sort_shell_int(
        edu::shell_sort<decltype(integer_mat->get_iterator())>, *integer_mat,
        "shell_sort_int");
    tread_vector.emplace_back(sort_shell_int);

    sortMeter bit_sort_int(
      edu::radix_sort<decltype(integer_mat->get_iterator())>, *integer_mat,
      "radix_sort_intt");
      tread_vector.emplace_back(bit_sort_int);
    
    sortMeter pdqsort(
      ::pdqsort<decltype(integer_mat->get_iterator())>, *integer_mat,
      "PDQD SORT INT");
      tread_vector.emplace_back(pdqsort);
    


    //clang-format on
}

  for (auto &t : tread_vector) {
    t.join();
  }


}