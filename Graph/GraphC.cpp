#include <iostream>
#include <vector>


class TGraph {
public:
    enum EColor {
        White,
        Gray,
        Black
    };
    
    TGraph(uint32_t size) 
        : Size(size)
        , Graph(size, std::vector<uint32_t>(size)) {}
        
    void ReadFromStream(std::istream& stream);
    bool HasCycle() const;

private:
    bool DepthFirstSearch(std::vector<EColor>& status, uint32_t vertex) const;

private:
    uint32_t Size;
    std::vector<std::vector<uint32_t>> Graph;
};


void TGraph::ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < Size; ++i) {
        for (uint32_t j = 0; j < Size; ++j) {
            stream >> Graph[i][j];
        }
    }
}


bool TGraph::DepthFirstSearch(std::vector<EColor>& status, uint32_t vertex) const {
    status[vertex] = Gray; 
    for (uint32_t i = 0; i < Size; ++i) {	
        if (Graph[vertex][i] && status[i] == White) {
            if (DepthFirstSearch(status, i)) {
                return true;
            }
        } else if (Graph[vertex][i] && status[i] == Gray) {
            return true;
        }
    }
    status[vertex] = Black;
    return false;
}


bool TGraph::HasCycle() const {
    std::vector<EColor> status(Size, White);
    for (uint32_t i = 0; i < Size; ++i) {
        if (DepthFirstSearch(status, i)) {
            return true;
        }
    }
    return false;
}


int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    std::cout << graph.HasCycle() << std::endl;
    return 0;
}

