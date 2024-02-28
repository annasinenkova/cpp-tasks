#include <iostream>
#include <vector>
#include <cmath>

class TGraph {
public:
    TGraph(uint64_t size = 0)
        : Size(size)
        , InTime(size + 1)
        , OutTime(size + 1) 
        , Graph(size)
        , Ancestors(size, std::vector<uint64_t>(std::log2(size) + 1, 0)) {}

    void ReadFromStream(std::istream& stream);
    uint64_t FindLCA(uint64_t vertex1, uint64_t vertex2) const;

private:
    void Build();
    bool IsVertexAncestor(uint64_t vertex1, uint64_t vertex2) const;
    void DepthFirstSearch(uint64_t vertex, uint64_t& time, uint64_t parent);

private:
    size_t Size;
    std::vector<uint64_t> InTime;
    std::vector<uint64_t> OutTime;
    std::vector<std::vector<uint64_t>> Graph;
    std::vector<std::vector<uint64_t>> Ancestors;
};

void TGraph::ReadFromStream(std::istream& stream) {
    for (size_t i = 1; i < Graph.size(); ++i) {
        uint64_t j = 0; 
        stream >> j;
        Graph[j].push_back(i);
    }
    Build();
}

void TGraph::Build() {
    uint64_t time = 0;
    DepthFirstSearch(0, time, 0);
}

void TGraph::DepthFirstSearch(uint64_t vertex, uint64_t& time, uint64_t parent = 0) {
    InTime[vertex] = ++time;
    Ancestors[vertex][0] = parent;
    for (size_t i = 1; i <= std::log2(Size); ++i) {
        Ancestors[vertex][i] = Ancestors[Ancestors[vertex][i - 1]][i - 1];
    }
    for (const auto& edge : Graph[vertex]) {
        DepthFirstSearch(edge, time, vertex);
    }
    OutTime[vertex] = ++time;
}

bool TGraph::IsVertexAncestor(uint64_t vertex1, uint64_t vertex2) const {
    return InTime[vertex1] <= InTime[vertex2] && OutTime[vertex1] >= OutTime[vertex2];
}

uint64_t TGraph::FindLCA(uint64_t vertex1, uint64_t vertex2) const {
    if (IsVertexAncestor(vertex1, vertex2)) {
        return vertex1;
    }
    if (IsVertexAncestor(vertex2, vertex1)) {
        return vertex2;
    }
    for (int64_t i = std::log2(Size); i >= 0; --i) {
        if (!IsVertexAncestor(Ancestors[vertex1][i], vertex2)) {
            vertex1 = Ancestors[vertex1][i];
        }
    }
    return Ancestors[vertex1][0];
}

int main() {
    uint64_t n, m;
    std::cin >> n >> m;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    uint64_t a1, a2, x, y, z;
    std::cin >> a1 >> a2 >> x >> y >> z;
    uint64_t sum = 0;
    uint64_t v = graph.FindLCA(a1, a2);
    sum += v;
    for (size_t i = 1; i < m; ++i) {
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
        v = graph.FindLCA((a1 + v) % n, a2);
        sum += v;
    }
    std::cout << sum << std::endl;
    return 0;
}
