#define DEBUG_BIT 1
#if DEBUG_BIT
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <vector>

template <typename T, typename U>
struct weightedInterval {
    T start;
    T end;
    U weight;
};

template <typename T, typename U>
struct knapsackItem {
    T value;
    U weight;
};

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


int fib(int n) {
    int a = 0, b = 1;
    for (int i = 1; i < n; ++i) {
        b += a;
        a = b - a;
    }
    return a;
}

// INTERVALS SCHEDULING WITH WEIGHTS
template <typename T, typename U>
U scheduleIntervals(
    std::vector<weightedInterval<T,U>> intervals
) {
    std::vector<weightedInterval<T,U>> sortedIntervals = intervals;

    // Pre-processing to find non-overlapping preceding intervals for each interval
    std::vector<T> pre;
    pre.resize(intervals.size());

    std::sort(
        sortedIntervals.begin(),
        sortedIntervals.end(),
        [](auto& a, auto& b) {
            return a.start < b.start;
        }
    );
    int i = 0;
    for (int k = 0; k < intervals.size(); ++k) {
        if (k > 0) {

        } else {
            while (i < intervals.size() && sortedIntervals[i].start < sortedIntervals[k].end) {
                pre[i] = k;
                ++i;
            }
        }
    }

    // RECURRENCE
    std::vector<int> maxWithIntervals1TOi;
    maxWithIntervals1TOi.resize(intervals.size() + 1);
    for (int m = 0; m <= intervals.size(); ++m) {
        if (m == 0) {
            maxWithIntervals1TOi[0] = 0;
        } else {
            maxWithIntervals1TOi[m] = std::max(
                maxWithIntervals1TOi[m-1],
                maxWithIntervals1TOi[pre[m]] + intervals[m].weight
            );
        }
    }

    return maxWithIntervals1TOi[intervals.size()];
}

// 0/1-KNAPSACK PROBLEM
template <typename T, typename U>
T knapsackMaxValue(
    std::vector<knapsackItem<T,U>> items,
    U capacityWeight
) {
    std::vector< std::vector<T> > maxValues;
    int n = items.size();

    maxValues.resize(capacityWeight + 1);
    for (int i = 0; i <= capacityWeight; ++i) {
        maxValues[i].resize(n + 1);
    }

    // SETUP COMPLETE
    for (int i = 0; i <= capacityWeight; ++i) {
        maxValues[i][0] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        maxValues[0][i] = 0;
    }

    for (int i = 1; i <= n; ++i) {

        for (int w = 1; w <= capacityWeight; ++w) {
            if (items[i-1].weight > w) {
                maxValues[w][i] = maxValues[w][i-1];
            } else {
                T a = maxValues[w - items[i-1].weight][i-1] + items[i-1].value;
                T b = maxValues[w][i-1];
                maxValues[w][i] = std::max(a,b);
            }
            // std::cout << "(w, i) = {" << w << ", " << i << "}: " << maxValues[w][i] << '\n';
        }
    }
    return maxValues[capacityWeight][n];
}

// LONGEST INCREASING SUBSEQUENCE
template <typename T>
size_t longestIncreasingSubsequence(
    std::vector<T>& vec
) {
    std::vector<T> longestSoFarEndingHere(vec.size());
    size_t max = 0;

    longestSoFarEndingHere[0] = 1;
    for (int i = 1; i < vec.size(); ++i) {
        longestSoFarEndingHere[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (vec[j] < vec[i]) {
                longestSoFarEndingHere[i] = std::max(
                    longestSoFarEndingHere[i],
                    longestSoFarEndingHere[j] + 1
                );
            }
        }
        if (longestSoFarEndingHere[i] > max)
            max = longestSoFarEndingHere[i];
    }
    return max;
}

// LONGEST COMMON SUBSEQUENCE PROBLEM
size_t longestCommonSubsequence(std::string& a, std::string& b) {
    size_t aSize = a.size(), bSize = b.size();
    std::vector< std::vector<int> > M;
    M.resize(aSize + 1);
    for (int i = 0; i <= aSize; ++i) {
        M[i].resize(bSize + 1);
    }

    for (int i = 0; i <= aSize; ++i) {
        M[i][0] = 0;
    }
    for (int i = 0; i <= bSize; ++i) {
        M[0][i] = 0;
    }

    for (int i = 1; i <= aSize; ++i) {
        for (int j = 1; j <= bSize; ++j) {
            if (a[i] == b[j]) {
                M[i][j] = M[i-1][j-1] + 1;
                M[i][j] = std::max(M[i][j-1], M[i][j]);
                M[i][j] = std::max(M[i][j], M[i-1][j]);
            } else {
                M[i][j] = std::max(M[i][j-1], M[i-1][j]);
            }
        }
    }
    return M[aSize][bSize];
}

// MINIMUM EDIT DISTANCE
size_t minEditDistance(std::string& a, std::string& b) {
    size_t aSize = a.size(), bSize = b.size();
    std::vector< std::vector<int> > M;
    M.resize(aSize + 1);
    for (int i = 0; i <= aSize; ++i) {
        M[i].resize(bSize + 1);
    }

    for (int i = 0; i <= aSize; ++i) {
        M[i][0] = i;
    }
    for (int i = 0; i <= bSize; ++i) {
        M[0][i] = i;
    }

    // SETUP COMPLETE

    for (int i = 1; i <= aSize; ++i) {
        for (int j = 1; j <= bSize; ++j) {
            size_t prev = M[i-1][j-1];
            if (!(a[i] == b[j])) prev++;
            M[i][j] = prev;
            M[i][j] = std::min(M[i][j], M[i-1][j] + 1);
            M[i][j] = std::min(M[i][j], M[i][j-1] + 1);
        }
    }
    return M[aSize][bSize];
}

int main() {
    std::cout << fib(1) << '\n';
    std::cout << fib(2) << '\n';
    std::cout << fib(3) << '\n';
    std::cout << fib(4) << '\n';
    std::cout << fib(5) << '\n';
    std::cout << fib(10) << '\n';

    std::vector<weightedInterval<int, int>> scheduleVec{
        {2,8,6}, {2,4,2}, {5,6,1}, {7,9,2}
    };
    std::cout << scheduleIntervals<int, int>(scheduleVec) << '\n';

    std::vector<knapsackItem<int, int>> knapsackItems1 {
        {2,3}, {3,4}, {1,6}, {5,5}
    };
    std::cout << knapsackMaxValue<int, int>(knapsackItems1, 8) << '\n';

    std::vector<int> increasingSubVec1{
        7, 1, 3, 10, 11, 5, 19
    };
    std::cout << longestIncreasingSubsequence<int>(increasingSubVec1) << '\n';

    std::string a1 = "blurry", b1 = "burger";
    std::cout << longestCommonSubsequence(a1, b1) << "\n";

    std::string a2 = "snowy", b2 = "sunny";
    std::cout << minEditDistance(a2, b2) << "\n";
}
