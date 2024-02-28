#include <iostream>
#include <vector>
#include <queue>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), Graph(size) {}
    void ReadFromStream(std::istream& stream);
    void PrintMinTime(std::ostream& stream, const std::vector<uint32_t>& startVertices) const;

private:
    std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const;

private:
    uint32_t Size;
    std::vector<std::vector<uint32_t>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    uint32_t m, j, k;
    stream >> m;
    for (uint32_t i = 0; i < m; ++i) {
        stream >> j >> k;
        Graph[j - 1].push_back(k - 1);
        Graph[k - 1].push_back(j - 1);
    }
}

std::vector<uint32_t> TGraph::BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const {
    std::queue<uint32_t> q;
    std::vector<bool> used(Size, false);
    std::vector<uint32_t> minTime(Size, 0);
    for (uint32_t i = 0; i < startVertices.size(); ++i) {
        uint32_t vertex = startVertices[i];
        q.push(vertex);
        used[vertex] = true;
    }
    while (!q.empty()) {
        uint32_t vertex = q.front();
        q.pop();
        for (uint32_t i = 0; i < Graph[vertex].size(); ++i) {
            uint32_t nextVertex = Graph[vertex][i];
            if (!used[nextVertex]) {
                used[nextVertex] = true;
                q.push(nextVertex);
                minTime[nextVertex] = minTime[vertex] + 1;
            }
        }
    }
    return minTime;
}

void TGraph::PrintMinTime(std::ostream& stream) const {
    std::vector<uint32_t> startVertices = ReadExits(std::cin);
    std::vector<uint32_t> minTime = BreadthFirstSearch(startVertices);
    for (uint32_t i = 0; i < minTime.size(); ++i) {
        stream << minTime[i] << " ";
    }
    stream << std::endl;
}

std::vector<uint32_t> ReadExits(std::istream& stream) {
    uint32_t k, j;
    stream >> k;
    std::vector<uint32_t> exits;
    for (uint32_t i = 0; i < k; ++i) {
        stream >> j;
        exits.push_back(j - 1);
    }
    return exits;
}

int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    graph.PrintMinTime(std::cout, startVertices);
    return 0;
}

