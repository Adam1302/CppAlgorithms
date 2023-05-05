#define DEBUG_MODE 1
#if DEBUG_MODE
#define LOG(x) std::cout << x << "\n";
#else
#define LOG(x)
#endif

#include <iostream>
#include <vector>
#include <span>


namespace stringMatching {
    namespace kmp {

        void failureArray(std::string& s, int* failures) {
            
            failures[0] = 0;

            int stringIndex = 1, arrIndex = 0;

            while (stringIndex < s.size()) {
                if (s[stringIndex] == s[arrIndex]) {
                    ++arrIndex;
                    failures[stringIndex] = arrIndex;
                    ++stringIndex;
                } else if (arrIndex > 0) {
                    arrIndex = failures[arrIndex - 1];
                } else {
                    failures[stringIndex] = 0;
                    ++stringIndex;
                }
            }
        }

        int indexOf(std::string& text, std::string& pattern) {
            int* failures = new int[pattern.size()];
            failureArray(pattern, failures);

            int textIndex = 0, patternIndex = 0;

            while (textIndex < text.size()) {
                if (text[textIndex] == pattern[patternIndex]) {
                    if (patternIndex + 1 == pattern.size()) {
                        // the full pattern has been matched
                        return textIndex - pattern.size() + 1;
                    } else {
                        ++textIndex;
                        ++patternIndex;
                    }
                } else if (patternIndex > 0) {
                    patternIndex = failures[patternIndex - 1];
                } else {
                    ++textIndex;
                }
            }

            return -1;
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
    std::string haystack1 = "ababababaca";
    std::string needle1 = "ababaca";
    std::string needle2 = "ca";
    std::string needle3 = "aabaca";
    std::cout << stringMatching::kmp::indexOf(haystack1, needle1) << "\n";
    std::cout << stringMatching::kmp::indexOf(haystack1, needle2) << "\n";
    std::cout << stringMatching::kmp::indexOf(haystack1, needle3) << "\n";
}
