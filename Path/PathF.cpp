#include <iostream>
#include <vector>
#include <queue>

class TGraph {
public:
    TGraph(uint64_t size) : Size(size), Graph(size) {}
    void ReadFromStream(std::istream& stream);
    int64_t FindMinPath(uint64_t from, uint64_t to) const;
    
private:
    void Dijkstra(std::vector<uint64_t>& minDist, uint64_t from) const;

private:
    enum { INF = 1'000'000'000'000 };
    
    uint64_t Size;
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    uint64_t k = 0;
    stream >> k;
    for (size_t i = 0; i < k; ++i) {
        uint64_t from, to, dist;
        stream >> from >> to >> dist;
        Graph[from - 1].emplace_back(to - 1, dist);
        Graph[to - 1].emplace_back(from - 1, dist);
    }
}

void TGraph::Dijkstra(std::vector<uint64_t>& minDist, uint64_t from) const {
    std::priority_queue<std::pair<int64_t, uint64_t>> q;
    q.emplace(0, from);
    while (!q.empty()) {
        uint64_t vertex = q.top().second;
        uint64_t verDist = -q.top().first;
        q.pop();
        if (verDist > minDist[vertex]) {
            continue;
        }
        for (const auto& edge : Graph[vertex]) {
            int64_t to = edge.first;
            int64_t dist = edge.second;
            if (minDist[vertex] + dist < minDist[to]) {
                minDist[to] = minDist[vertex] + dist;
                q.emplace(-minDist[to], to);
            }
        }
    }
}

int64_t TGraph::FindMinPath(uint64_t from, uint64_t to) const {
    std::vector<uint64_t> minDist(Size, INF);
    minDist[from] = 0;
    Dijkstra(minDist, from);
    if (minDist[to] == INF) {
        return -1;
    }
    return minDist[to];
}

int main() {
    uint64_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    uint64_t from, to;
    std::cin >> from >> to;
    std::cout << graph.FindMinPath(--from, --to) << std::endl;
    return 0;
}

