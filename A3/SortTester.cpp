class SortTester {
private:
    ArrayGenerator generator;
    AllSorts sorter;

public:
    SortTester() : generator() {}

    std::string arrayTypeToString(ArrayType type) {
        switch (type) {
            case ArrayType::Random:
            return "Random";
            case ArrayType::Reverse:
            return "Reverse";
            case ArrayType::Almost:
            return "Almost";
        }
    }

    long long testQuickSort(std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        sorter.quickSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    long long testIntroSort(std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        sorter.introSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    long long MedTime(int size, ArrayType type, bool useIntroSort = false, int tests = 5) {
        std::vector<long long> times;
        std::vector<int> bigArray = generator.generateArray(type, 1000000);

        for (int i = 0; i < tests; i++) {
            std::vector<int> testArray = generator.subArr(bigArray, size);
            if (useIntroSort) {
                times.push_back(testIntroSort(testArray));
            } else {
                times.push_back(testQuickSort(testArray));
            }
        }

        std::sort(times.begin(), times.end());
        return times[times.size() / 2];
    }

    void Tests() {
        std::vector<int> sizes;
        for (int size = 500; size <= 100000; size += 100) {
            sizes.push_back(size);
        }
        std::vector<ArrayType> types = {ArrayType::Random, ArrayType::Reverse,ArrayType::Almost};

        for (const auto& arrayType : types) {
            std::string filename = "quick_sort_" + arrayTypeToString(arrayType) + ".csv";
            std::ofstream file(filename);
            file << "Size;Time\n";

            for (int size : sizes) {
                long long time = MedTime(size, arrayType, false);
                file << size << ";" << time << "\n";
            }
            file.close();
        }

        for (const auto& arrayType : types) {
            std::string filename = "intro_sort_" + arrayTypeToString(arrayType) + ".csv";
            std::ofstream file(filename);
            file << "Size;Time\n";

            for (int size : sizes) {
                long long time = MedTime(size, arrayType, true);
                file << size << ";" << time << "\n";
            }
            file.close();
        }
    }
};
