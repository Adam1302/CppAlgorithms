#define DEBUG_MODE 1
#if DEBUG_MODE
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <vector>

namespace sorting {

    namespace mergesort {
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

    namespace quicksort {
        template <typename T>
        int partition(std::vector<T>& vec, int pivot) {
            std::swap(vec[vec.size() - 1], vec[pivot]);

            int left = 0, right = vec.size() - 2;
            T& pivotVal = vec[pivot];

            while (true) {
                while (vec[left] < pivotVal) left++;
                while (vec[right] > pivotVal) right--;

                if (left >= right) break;
                else std::swap(vec[left], vec[right]);
            }

            std::swap(vec[vec.size() - 1], vec[left]);

            return left;
        }

        template <typename T>
        int partition(std::vector<T>& vec, int pivot, int left, int right) {
            int adjustedLen = right + 1;

            std::swap(vec[adjustedLen - 1], vec[pivot]);
            T& pivotVal = vec[pivot];

            --right;

            while (true) {
                while (vec[left] < pivotVal) left++;
                while (vec[right] > pivotVal) right--;

                if (left >= right) break;
                else std::swap(vec[left], vec[right]);
            }

            std::swap(vec[adjustedLen - 1], vec[left]);

            return left;
        }

        template <typename T>
        T quickSelect(std::vector<T>& vec, int wanted) {
            int pivot = vec.size() - 1;

            int i = partition(vec, pivot);

            if (i == wanted) return vec[i];
            else if (i > wanted) {
                std::vector<T> tempVec{vec.begin(), vec.begin() + i};
                return quickSelect(tempVec, wanted);
            }
            // i < wanted
            std::vector<T> tempVec{vec.begin() + i + 1, vec.end()};
            return quickSelect(tempVec, wanted - i - 1);
        }

        template <typename T>
        void quickSort(std::vector<T>& vec, int left, int right) {
            if (right - left < 1) return;

            int pivot = right;
            int midVal = partition(vec, pivot, left, right);

            quickSort(vec, left, midVal - 1);
            quickSort(vec, midVal + 1, right);
        }

        template <typename T>
        void quickSort(std::vector<T>& vec) {
            if (vec.size() < 2) return;

            quickSort(vec, 0, vec.size() - 1);
        }
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
    std::vector<int> vec1{4, 1, 6, 2, 3, 5};
    std::cout << vec1 << "\n";
    sorting::mergesort::mergesort(vec1);
    std::cout << vec1 << "\n";

    std::vector<std::string> fourSeasons{"Tommy", "Frankie", "Nick", "Bob"};
    std::cout << fourSeasons << "\n";
    sorting::mergesort::mergesort(fourSeasons);
    std::cout << fourSeasons << "\n";

    std::vector<int> partitionTest{30, 60, 10, 0, 50, 80, 90, 20, 40, 70};
    std::cout << partitionTest << "\n";
    sorting::quicksort::partition(partitionTest, partitionTest.size() - 1);
    std::cout << partitionTest << "\n";

    std::vector<int> quickSelectTest{30, 60, 10, 0, 50, 80, 90, 20, 40, 70};
    std::cout << sorting::quicksort::quickSelect(quickSelectTest, 4) << "\n";
    std::cout << sorting::quicksort::quickSelect(quickSelectTest, 6) << "\n";

    std::cout << partitionTest << "\n";
    sorting::quicksort::quickSort(partitionTest);
    std::cout << partitionTest << "\n";
}
