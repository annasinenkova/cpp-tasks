#include <iostream>
#include <algorithm>
#include <vector>


class TGraph {
public:
    enum EColors {
        White,
        Gray,
        Black
    };
    TGraph(uint32_t size) : Size(size), Graph(size, std::vector<uint32_t>(size)) {}
    void ReadFromStream(std::istream& stream, const uint32_t pairSize);
    void PrintComponentNum(std::ostream& stream) const;

private:
    bool DepthFirstSearch(std::vector<EColors>& status, std::vector<uint32_t>& order, const uint32_t vertex) const;

private:
    uint32_t Size;
    std::vector<std::vector<uint32_t>> Graph;
};


void TGraph::ReadFromStream(std::istream& stream, const uint32_t pairSize) {
    uint32_t j, k;
    for (uint32_t i = 0; i < pairSize; ++i) {
        stream >> j >> k;
        Graph[j - 1][k - 1] = 1;
    }
}


bool TGraph::DepthFirstSearch(std::vector<EColors>& status, std::vector<uint32_t>& order, const uint32_t vertex) const {
    status[vertex] = Gray; 
    for (uint32_t i = 0; i < Size; ++i) {	
        if (Graph[vertex][i] && status[i] == White) {
            if (DepthFirstSearch(status, order, i)) {
                return true;
            }
        }
        else if (Graph[vertex][i] && status[i] == Gray) {
            return true;
        }
    }
    order.push_back(vertex);
    status[vertex] = Black;
    return false;
}


void TGraph::PrintComponentNum(std::ostream& stream) const {
    std::vector<EColors> status(Size, White);
    std::vector<uint32_t> order;
    for (uint32_t i = 0; i < Size; ++i) {
        if (status[i] == White && DepthFirstSearch(status, order, i)) {
            stream << "No" << std::endl;
            return;
        }
    }
    std::reverse(order.begin(), order.end());
    stream << "Yes" << std::endl;
    for (uint32_t i = 0; i < order.size(); ++i) {
        stream << order[i] + 1 << " ";
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
    graph.PrintSoldiersOrder(std::cout);
    return 0;
}

