#include <iostream>
#include <vector>
#include <cmath>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), Graph(size) {}
    void ReadFromStream(std::istream& stream);
    double FindMinPath(uint32_t from, uint32_t to, std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& specialPaths) const;

private:
    enum { INF = 1'000'000'000 };

    uint32_t Size;
    std::vector<std::pair<int32_t, int32_t>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    for (size_t i = 0; i < Size; ++i) {
        stream >> Graph[i].first;
        stream >> Graph[i].second;
    }
}

double TGraph::FindMinPath(uint32_t from, uint32_t to, std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& specialPaths) const {
    std::vector<bool> used(Size, false);
    std::vector<double> minDist(Size, INF);
    minDist[from] = 0;
    while (true) {
        uint32_t vertex = Size;
        for (size_t i = 0; i < Size; ++i) {
            if (!used[i] && (vertex == Size || minDist[i] < minDist[vertex])) {
                vertex = i;
            }
        }
        if (vertex == Size) {
            break;
        }
        used[vertex] = true;
        for (size_t i = 0; i < Size; ++i) {
            if (vertex != i) {
            double dist = 0;
                bool flag = false;
                for (size_t j = 0; j < specialPaths[vertex].size(); ++j) {
                    if (specialPaths[vertex][j].first == i) {
                        dist = specialPaths[vertex][j].second;
                        flag = true;
                    }
                }
                if (!flag) {
                    int64_t a = Graph[vertex].first - Graph[i].first;
                    int64_t b = Graph[vertex].second - Graph[i].second;
                    dist = sqrt(a*a + b*b);
                }
                if (minDist[vertex] + dist < minDist[i]) {
                    minDist[i] = minDist[vertex] + dist;
                }
            }
        }
    }
    return minDist[to];
}

std::vector<std::vector<std::pair<uint32_t, uint32_t>>> ReadSpecialPathsFromStream(std::istream& stream, uint32_t n) {
    uint32_t m = 0;
    stream >> m;
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> specialPaths(n);
    for (size_t i = 0; i < m; ++i) {
        int32_t from, to, dist;
        stream >> from >> to >> dist;
        specialPaths[from - 1].push_back(std::pair<uint32_t, uint32_t>(to - 1, dist));
        specialPaths[to - 1].push_back(std::pair<uint32_t, uint32_t>(from - 1, dist));
    }
    return specialPaths;
}

int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> specialPaths = ReadSpecialPathsFromStream(std::cin, n);
    uint32_t from, to;
    std::cin >> from >> to;
    std::cout << graph.FindMinPath(--from, --to, specialPaths) << std::endl;
    return 0;
}

