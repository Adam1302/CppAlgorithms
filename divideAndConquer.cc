#define DEBUG_MODE 0
#if DEBUG_MODE
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <vector>


namespace sorting {
    template<typename T>
    void merge(std::vector<T>& vec, int left, int mid, int right, std::vector<T>& sortedVec) {
        for (int i = left; i <= right; ++i) sortedVec[i] = vec[i];

        int iLeft = left, iRight = mid + 1;

        for (int k = left; k <= right; ++k) {
            if (iLeft > mid) vec[k] = sortedVec[iRight++];
            else if (iRight > right) vec[k] = sortedVec[iLeft++];
            else if (sortedVec[iLeft] <= sortedVec[iRight]) vec[k] = sortedVec[iLeft++];
            else vec[k] = sortedVec[iRight++];
        }
    }

    template<typename T>
    void mergesort(std::vector<T>& vec, int left, int right, std::vector<T>& sortedVec) {
        if (sortedVec.size() == 0) {
            sortedVec.resize(vec.size());
        }

        if (right <= left) return;

        int mid = (left + right) / 2;

        mergesort(vec, left, mid, sortedVec);
        mergesort(vec, mid + 1, right, sortedVec);
        merge(vec, left, mid, right, sortedVec);
    }

    template<typename T>
    void mergesort(std::vector<T>& vec) {
        std::vector<T> vecToBeSorted;
        mergesort(vec, 0, vec.size() - 1, vecToBeSorted);
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
    out << "{";
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i != vec.size() - 1) out << ", ";
    }
    out << "}";
    return out;
}

int main() {
    LOG("Hello World");

    std::vector<int> vec1{4, 1, 6, 2, 3, 5};
    std::cout << vec1 << "\n";
    sorting::mergesort(vec1);
    std::cout << vec1 << "\n";
}
