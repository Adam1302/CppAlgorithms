#define DEBUG_MODE 1
#if DEBUG_MODE
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <vector>

namespace searching {
    template<typename T>
    int binarySearch(std::vector<T>& vec, const T& key) {
        int left = 0, right = vec.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (vec[mid] > key) right = mid - 1;
            else if (vec[mid] < key) left = mid + 1;
            else return mid;
        }
        return -1;
    }

    int interpolationSearch(std::vector<int>& vec, int key) {
        int left = 0, right = vec.size() - 1, mid;

        while (left <= right) {
            if (key < vec[left] || key > vec[right]) return -1;
            if (key == vec[right]) return right;

            mid = left + ((right - left) * ((key - vec[left])/(vec[right] - vec[left])));

            if (vec[mid] == key) return mid;
            else if (vec[mid] < key) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    out << "{";
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        out << vec[i] << ", ";
    }
    if (vec.size() != 0) out << vec[vec.size() - 1];
    out << "}";

    return out;
}

int main() {
    std::vector<int> searchTest{0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::cout << searching::binarySearch(searchTest, 10) << "\n";
    std::cout << searching::binarySearch(searchTest, 80) << "\n";
    std::cout << searching::interpolationSearch(searchTest, 10) << "\n";
    std::cout << searching::interpolationSearch(searchTest, 80) << "\n";
}

