#include <iostream>
#include <numeric>
#include <vector>

uint32_t FindLevenshteinDistance(const std::string& str1, const std::string& str2) {
    std::vector<std::vector<uint32_t>> dist(str1.size() + 1, std::vector<uint32_t>(str2.size() + 1));
    std::iota(dist[0].begin(), dist[0].end(), 0);
    for (size_t i = 0; i < str1.size(); ++i) {
        dist[i + 1][0] = i + 1;
        for (size_t j = 0; j < str2.size(); ++j) {
            dist[i + 1][j + 1] = std::min(std::min(dist[i][j + 1], dist[i + 1][j]) + 1, (str1[i] != str2[j]) + dist[i][j]);
        }
    }
    return dist[str1.size()][str2.size()];
}

int main() {
    std::string str1, str2;
    std::cin >> str1 >> str2;
    std::cout << FindLevenshteinDistance(str1, str2) << std::endl;
    return 0;
}