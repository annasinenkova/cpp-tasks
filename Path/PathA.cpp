#include <iostream>
#include <vector>

class TGraph {
public:
    TGraph(uint32_t size) : Size(size), Graph(size, std::vector<int32_t>(size, 0)) {}
    void ReadFromStream(std::istream& stream);
    std::vector<std::vector<int32_t>> FindMinPathMatrix() const;

private:
    uint32_t Size;
    std::vector<std::vector<int32_t>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < Size; ++i) {
        for (uint32_t j = 0; j < Size; ++j) {
            stream >> Graph[i][j];
        }
    }
}

std::vector<std::vector<int32_t>> TGraph::FindMinPathMatrix() const {
    std::vector<std::vector<int32_t>> minPath = Graph;
    for (uint32_t i = 0; i < Size; ++i) {
        for (uint32_t j = 0; j < Size; ++j) {
            for (uint32_t k = 0; k < Size; ++k) {
                if (minPath[j][i] + minPath[i][k] < minPath[j][k]) {
                    minPath[j][k] = minPath[j][i] + minPath[i][k];
                }
            }
        }
    }
    return minPath;
}

void WriteMatrixToStream(const std::vector<std::vector<int32_t>>& matrix, std::ostream& stream) {
    for (uint32_t i = 0; i < matrix.size(); ++i) {
        for (uint32_t j = 0; j < matrix.size(); ++j) {
            stream << matrix[i][j] << " ";
        }
        stream << std::endl;
    }
}

int main() {
    uint32_t n = 0;
    std::cin >> n;
    TGraph graph(n);
    graph.ReadFromStream(std::cin);
    std::vector<std::vector<int32_t>> minPath = graph.FindMinPathMatrix();
    WriteMatrixToStream(minPath, std::cout);
    return 0;
}

