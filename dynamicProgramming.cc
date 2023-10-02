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

int main() {
    std::cout << fib(1) << '\n';
    std::cout << fib(2) << '\n';
    std::cout << fib(3) << '\n';
    std::cout << fib(4) << '\n';
    std::cout << fib(5) << '\n';
    std::cout << fib(10) << '\n';

    std::vector<weightedInterval<int, int>> vec1{
        {2,8,6}, {2,4,2}, {5,6,1}, {7,9,2}
    };
    std::cout << scheduleIntervals<int, int>(vec1) << '\n';
}
