class ArrayGenerator {
 private:
  std::mt19937 g;

 public:
  ArrayGenerator() : g(52) {}

  std::vector<int> generateArray(ArrayType type, int size = 100000,
                                 int swaps = 10) {
    switch (type) {
      case ArrayType::Random:
        return randomArr(size);
      case ArrayType::Reverse:
        return reverseArr(size);
      case ArrayType::Swaps:
        return SortedArr(swaps, size);
    }
  }

  std::vector<int> randomArr(int size = 100000, int min = 0, int max = 6000) {
    std::vector<int> arr(size);
    std::uniform_int_distribution<int> rnd(min, max);

    for (int i = 0; i < size; ++i) {
      arr[i] = rnd(g);
    }

    return arr;
  }

  std::vector<int> reverseArr(int size = 100000) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
      arr[i] = size - i;
    }
    return arr;
  }

  std::vector<int> SortedArr(int swaps, int size = 100000) {
    std::vector<int> arr(size);

    for (int i = 0; i < size; i++) {
      arr[i] = i + 1;
    }

    std::uniform_int_distribution<int> rnd(0, size - 1);

    for (int l = 0; l < swaps; l++) {
      int i = rnd(g);
      int j = rnd(g);
      std::swap(arr[i], arr[j]);
    }

    return arr;
  }

  std::vector<int> subArr(const std::vector<int>& arr, int size) {
    return std::vector<int>(arr.begin(), arr.begin() + size);
  }
};