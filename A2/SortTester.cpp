class SortTester {
 private:
  ArrayGenerator generator;
  AllSorts sorter;

 public:
  SortTester() : generator() {}

  long long testMergeSort(std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.mergeSort(arr, 0, arr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed)
        .count();
  }

  long long testCombSort(std::vector<int> arr, int threshold) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.combSort(arr, 0, arr.size() - 1, threshold);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed)
        .count();
  }

  long long sortArray(std::vector<int> arr, Algorithm algorithm,
                      int threshold = 0) {
    auto start = std::chrono::high_resolution_clock::now();

    switch (algorithm) {
      case Algorithm::Merge:
        sorter.mergeSort(arr, 0, arr.size() - 1);
        break;
      case Algorithm::Comb:
        sorter.combSort(arr, 0, arr.size() - 1, threshold);
        break;
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed)
        .count();
  }

  std::string arrayTypeToString(ArrayType type) {
    switch (type) {
      case ArrayType::Random:
        return "Random";
      case ArrayType::Reverse:
        return "Reverse";
      case ArrayType::Swaps:
        return "Almost";
      default:
        return "Unknown";
    }
  }

  long long MedTime(int size, ArrayType type, Algorithm algorithm,
                    int threshold = 0, int tests = 5) {
    std::vector<long long> times;
    std::vector<int> bigArray;

    bigArray = generator.generateArray(type);

    for (int i = 0; i < tests; i++) {
      std::vector<int> testArray = generator.subArr(bigArray, size);
      times.push_back(sortArray(testArray, algorithm, threshold));
    }

    std::sort(times.begin(), times.end());
    return times[times.size() / 2];
  }

  void Tests() {
    std::vector<int> sizes;
    for (int size = 500; size <= 100000; size += 100) {
      sizes.push_back(size);
    }

    std::vector<ArrayType> Types = {ArrayType::Random, ArrayType::Reverse,
                                    ArrayType::Swaps};
    std::vector<int> thresholds = {5, 10, 20, 30, 50};

    for (const auto& arrayType : Types) {
      std::string filename =
          "merge_sort_" + arrayTypeToString(arrayType) + ".csv";
      std::ofstream file(filename);
      file << "Array Size;Time\n";

      for (int size : sizes) {
        long long time = MedTime(size, arrayType, Algorithm::Merge);
        file << size << ";" << time << "\n";
      }
      file.close();
    }

    for (const auto& arrayType : Types) {
      for (int threshold : thresholds) {
        std::string filename = "comb_sort_" + arrayTypeToString(arrayType) +
                               "_threshold_" + std::to_string(threshold) +
                               ".csv";
        std::ofstream file(filename);
        file << "Array Size;Time\n";

        for (int size : sizes) {
          long long time = MedTime(size, arrayType, Algorithm::Comb, threshold);
          file << size << ";" << time << "\n";
        }
        file.close();
      }
    }
  }
};
