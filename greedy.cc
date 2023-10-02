#define DEBUG_MODE 0
#if DEBUG_MODE
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, std::pair<T, T> p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
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

template <typename T>
std::vector<std::pair<T, T>> maxDisjointIntervalScheduling(
    std::vector<std::pair<T, T>> intervals
) {
    std::vector<std::pair<T, T>> disjoints;
    std::sort(
        intervals.begin(),
        intervals.end(),
        [](auto& elem1, auto& elem2) {
            return elem1.second < elem2.second;
        }
    );
    T currentTime = intervals[0].second;
    disjoints.emplace_back(intervals[0]);
    for (int i = 0; i < intervals.size(); ++i) {
        if (currentTime > intervals[i].first) {
            continue;
        } else {
            disjoints.emplace_back(intervals[i]);
            currentTime = intervals[i].second;
        }
    }
    return disjoints;
}

template <typename T>
int minColoursNeeded(
    std::vector<std::pair<T, T>> intervals
) {
    std::sort(
        intervals.begin(),
        intervals.end(),
        [](auto& elem1, auto& elem2) {
            return elem1.first < elem2.first;
        }
    );
    
    std::priority_queue<int, std::vector<int>, std::greater<int>> finishTimes;
    size_t maxCount = 0;

    for (int i = 0; i < intervals.size(); ++i) {
        T current = intervals[i].first;
        while (!finishTimes.empty() && current > finishTimes.top()) {
            finishTimes.pop();
        }
        finishTimes.push(intervals[i].second);
        if (finishTimes.size() > maxCount)
            maxCount = finishTimes.size();
    }
    return maxCount;
}

int main() {
    LOG("Hello World");

    std::vector<std::pair<int, int>> vec1{
        {2,8}, {3,4}, {5,6}
    };
    std::vector<std::pair<int, int>> vec2{
        {2,4}, {3,5}, {4,6}, {5,7}, {6,8}
    };
    std::vector<std::pair<int, int>> vec3{
        {2,4}, {3,6}, {1,6}, {6,7}, {5,8}
    };
    std::cout << maxDisjointIntervalScheduling(vec1) << "\n";
    std::cout << maxDisjointIntervalScheduling(vec2) << "\n";

    std::cout << minColoursNeeded(vec2) << "\n";
    std::cout << minColoursNeeded(vec3) << "\n";
    // sorting::mergesort(vec1);
    // std::cout << vec1 << "\n";
}
