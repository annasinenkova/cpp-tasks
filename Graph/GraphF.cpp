#include <iostream>
#include <vector>
#include <stack>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), EdgesCount(0), Graph(size + 1) {}
    void ReadFromStream(std::istream& stream, uint32_t routesCount);
    void PrintRoute(std::ostream& stream);

private:
    void FindRoute(std::vector<uint32_t>& route, uint32_t vertex);

private:
    uint32_t Size;
    uint32_t EdgesCount;
    std::vector<std::stack<uint32_t>> Graph;
};


void TGraph::ReadFromStream(std::istream& stream, uint32_t routesCount) {
    uint32_t k, prevVertex, nextVertex;
    for (uint32_t i = 0; i < routesCount; ++i) {
        stream >> k >> prevVertex;
        EdgesCount += k;
        for (uint32_t j = 0; j < k; ++j) {
            stream >> nextVertex;
            Graph[prevVertex].push(nextVertex);
            prevVertex = nextVertex;
        }
    }
}


void TGraph::FindRoute(std::vector<uint32_t>& route, uint32_t vertex) {
    while (!Graph[vertex].empty()) {
        uint32_t next = Graph[vertex].top();
        if (next) {
            EdgesCount = EdgesCount - 1;
            Graph[vertex].pop();
            FindRoute(route, next);
        }
    }
    route.push_back(vertex);
}


void TGraph::PrintRoute(std::ostream& stream) {
    if (EdgesCount == 0) {
        stream << 0 << std::endl;
        return;
    }
    std::vector<uint32_t> route;
    uint32_t v = 0;
    while (!Graph[++v].size());
    FindRoute(route, v);
    if (EdgesCount) {
        stream << 0 << std::endl;
        return;
    }
    stream << route.size() << " ";
    for (uint32_t i = 0; i < route.size(); ++i) {
        stream << route[route.size() - i - 1] << " ";
    }
    stream << std::endl;
}


int main() {
    uint32_t n = 0, m = 0;
    std::cin >> n >> m;
    TGraph graph(m);
    graph.ReadFromStream(std::cin, n);
    graph.PrintRoute(std::cout);
    return 0;
}

