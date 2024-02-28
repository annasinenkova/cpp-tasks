#include <iostream>
#include <vector>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), Graph(size, std::vector<uint32_t>(size)) {}
    void ReadFromStream(std::istream& stream);
    std::vector<uint32_t> GetConnectedComponent(const uint32_t vertex) const;

private:
    void DepthFirstSearch(std::vector<bool>& used, std::vector<uint32_t>& comp, const uint32_t vertex) const;

private:
    uint32_t Size;
    std::vector<std::vector<uint32_t>> Graph;
};

void TGraph::DepthFirstSearch(std::vector<bool>& used, std::vector<uint32_t>& comp, const uint32_t vertex) const {
    used[vertex] = true;
    comp.push_back(vertex);
    for (uint32_t i = 0; i < Size; ++i) {
        if (Graph[vertex][i] && !used[i]) {
            DepthFirstSearch(used, comp, i);
        }
    }
}

std::vector<uint32_t> TGraph::GetConnectedComponent(const uint32_t vertex) const {
    std::vector<bool> used(Size, false);
    std::vector<uint32_t> comp;
    DepthFirstSearch(used, comp, vertex);
    return comp;
}

void TGraph::ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < Size; ++i) {
        for (uint32_t j = 0; j < Size; ++j) {
            stream >> Graph[i][j];
        }
    }
}

int main() {
    uint32_t n = 0;
    std::cin >> n;
    uint32_t s = 0;
    std::cin >> s; 
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    std::vector<uint32_t> connComp = graph.GetConnectedComponent(s - 1);
    std::cout << connComp.size() << std::endl;
    return 0;
}

