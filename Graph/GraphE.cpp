#include <iostream>
#include <vector>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), Graph(size), InvertGraph(size) {}
    void ReadFromStream(std::istream& stream, uint32_t pairSize);
    void PrintComponentNum(std::ostream& stream) const;

private:
    void DepthFirstSearch(std::vector<bool>& used, std::vector<uint32_t>& order, uint32_t vertex) const;
    void FindComponentNum(std::vector<uint32_t>& comp, uint32_t vertex, uint32_t compNum) const;

private:
    uint32_t Size;
    std::vector<std::vector<uint32_t>> Graph;
    std::vector<std::vector<uint32_t>> InvertGraph;
};


void TGraph::ReadFromStream(std::istream& stream, uint32_t pairSize) {
    uint32_t j, k;
    for (uint32_t i = 0; i < pairSize; ++i) {
        stream >> j >> k;
        Graph[j - 1].push_back(k - 1);
        InvertGraph[k - 1].push_back(j - 1);
    }
}


void TGraph::DepthFirstSearch(std::vector<bool>& used, std::vector<uint32_t>& order, uint32_t vertex) const {
    used[vertex] = true;
    for (uint32_t i = 0; i < Graph[vertex].size(); ++i) {
        if (!used[Graph[vertex][i]]) {
            DepthFirstSearch(used, order, Graph[vertex][i]);
        }
    }
    order.push_back(vertex);
}


void TGraph::FindComponentNum(std::vector<uint32_t>& comp, uint32_t vertex, uint32_t compNum) const {
    comp[vertex] = compNum;
    for (uint32_t i = 0; i < InvertGraph[vertex].size(); ++i) {
        if (!comp[InvertGraph[vertex][i]]) {
            FindComponentNum(comp, InvertGraph[vertex][i], compNum);
        }
    }
}


void TGraph::PrintComponentNum(std::ostream& stream) const {
    std::vector<bool> used(Size, false);
    std::vector<uint32_t> order;
    for (uint32_t i = 0; i < Size; ++i) {
        if (!used[i]) {
            DepthFirstSearch(used, order, i);
        }
    }
    uint32_t k = 0;
    std::vector<uint32_t> comp(Size, 0);
    for (uint32_t i = 0; i < Size; ++i) {
        uint32_t j = order[Size - 1 - i];
        if (!comp[j]) {
            FindComponentNum(comp, j, ++k);
        }
    }
    stream << k << std::endl;
    for (uint32_t i = 0; i < comp.size(); ++i) {
        stream << comp[i] << " ";
    }
    stream << std::endl;
}


int main() {
    uint32_t n = 0;
    std::cin >> n;
    uint32_t m = 0;
    std::cin >> m;
    TGraph graph(n);
    graph.ReadFromStream(std::cin, m);
    graph.PrintComponentNum(std::cout);
    return 0;
}

