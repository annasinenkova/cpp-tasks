#include <iostream>
#include <vector>
#include <queue>

class TGraph {
public:
    TGraph(uint32_t n, uint32_t k) : N(n), K(k), Graph(N + 1) {}
    void ReadFromStream(std::istream& stream);
    int FindMinSum() const;
    
private:
    uint32_t N, K;
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    for (size_t i = 1; i <= K; ++i) {
        uint32_t count = 0;
        stream >> count;
        for (size_t j = 0; j < count; ++j) {
            uint32_t a, b;
            stream >> a >> b;
            Graph[a - 1].emplace_back(b - 1, i);
            Graph[b - 1].emplace_back(a - 1, i);
        }
    }
}

int TGraph::FindMinSum() const {
    std::vector<std::vector<uint32_t>> sum(N, std::vector<uint32_t>(K + 1, N + 2));
    std::vector<std::vector<bool>> used(N, std::vector<bool>(K + 1, false));
    std::deque<std::pair<uint32_t, uint32_t>> q;
    q.emplace_back(0, 0);
    sum[0][0] = 0;
    while (!q.empty()) {
        uint32_t vertex = q.front().first;
        uint32_t prevMap = q.front().second;
        q.pop_front();
        if (!used[vertex][prevMap]) {  
            if (prevMap == 0) {
                for (size_t i = 1; i <= K; ++i) {
                    if (sum[vertex][i] > sum[vertex][prevMap] + 1) {
                        sum[vertex][i] = sum[vertex][prevMap] + 1;
                        q.emplace_back(vertex, i);  
                    }
                }
            } else {
                for (size_t i = 0; i < Graph[vertex].size(); ++i) {
                    uint32_t nextVertex = Graph[vertex][i].first;
                    uint32_t nextMap = Graph[vertex][i].second;
                    if (nextMap == prevMap) {
                        if (sum[nextVertex][nextMap] > sum[vertex][prevMap]) {
                            sum[nextVertex][nextMap] = sum[vertex][prevMap];
                            q.emplace_front(nextVertex, nextMap);
                        }
                    }
                }
                if (sum[vertex][0] > sum[vertex][prevMap]) {
                    sum[vertex][0] = sum[vertex][prevMap];
                    q.emplace_front(vertex, 0);
                }
            }
            used[vertex][prevMap] = true;
        }
    }
    if (sum[N - 1][0] == N + 2) {
        return -1;
    }
    return sum[N - 1][0];
}

int main() {
    uint32_t n = 0, k = 0;
    std::cin >> n >> k;
    TGraph graph(n, k);
    graph.ReadFromStream(std::cin);
    std::cout << graph.FindMinSum() << std::endl;
    return 0;
}

