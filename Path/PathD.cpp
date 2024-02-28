#include <iostream>
#include <vector>
#include <numeric>

class TDisjointSetUnion {
public:
    TDisjointSetUnion(uint32_t size);
    uint32_t FindSet(uint32_t vertex);
    bool IsSetComplete();
    void UnionSets(uint32_t reprO, uint32_t reprT);

private:
    uint32_t Size;
    std::vector<uint32_t> Rank;
    std::vector<uint32_t> Parent;
};

TDisjointSetUnion::TDisjointSetUnion(uint32_t size) : Size(size), Rank(size, 0), Parent(size) {
    std::iota(Parent.begin(), Parent.end(), 0);
}

uint32_t TDisjointSetUnion::FindSet(uint32_t vertex) {
    if (vertex == Parent[vertex]) {
        return vertex;
    }
    return Parent[vertex] = FindSet(Parent[vertex]);
}

bool TDisjointSetUnion::IsSetComplete() {
    uint32_t setNum = FindSet(0);
    for (uint32_t i = 1; i < Size; ++i) {
        if (FindSet(i) != setNum) {
            return false;
        }
    }
    return true;
}

void TDisjointSetUnion::UnionSets(uint32_t reprO, uint32_t reprT) {
    reprO = FindSet(reprO);
    reprT = FindSet(reprT);
    if (reprT != reprO) {
        if (Rank[reprO] > Rank[reprT]) {
            Parent[reprT] = reprO;
        } else {
            Parent[reprO] = reprT;
        }
        if (Rank[reprO] == Rank[reprT]) {
            ++Rank[reprT];
        }
    }
}

class TGraph {
public:
    TGraph(uint32_t n, uint32_t m) : N(n), M(m), Graph(n, std::vector<uint32_t>(m, 0)) {}
    void ReadFromStream(std::istream& stream);
    void PrintMinScheme() const;

private:
    uint32_t MST(std::vector<std::vector<uint32_t>>& newEdges) const;

private:
    uint32_t N, M;
    std::vector<std::vector<uint32_t>> Graph;
};

void TGraph::ReadFromStream(std::istream& stream) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            stream >> Graph[i][j];
        }
    }
}

uint32_t TGraph::MST(std::vector<std::vector<uint32_t>>& newEdges) const {
    uint32_t sum = 0;
    TDisjointSetUnion set(N * M);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (Graph[i][j] == 1 || Graph[i][j] == 3) {
                set.UnionSets(i * M + j, (i + 1) * M + j);
            }
            if (Graph[i][j] == 2 || Graph[i][j] == 3) {
                set.UnionSets(i * M + j, i * M + (j + 1));
            }
        }
    }
    for (uint32_t i = 0; i < N - 1; ++i) {
        for (uint32_t j = 0; j < M; ++j) {
            if (set.FindSet(i * M + j) != set.FindSet((i + 1) * M + j)) {
                set.UnionSets(i * M + j, (i + 1) * M + j);
                newEdges.push_back(std::vector<uint32_t>{i + 1, j + 1, 1});
                sum += 1;
            }
        }
    }
    for (uint32_t i = 0; i < N; ++i) {
        for (uint32_t j = 0; j < M - 1; ++j) {
            if (set.FindSet(i * M + j) != set.FindSet(i * M + (j + 1))) {
                set.UnionSets(i * M + j, i * M + (j + 1));
                newEdges.push_back(std::vector<uint32_t>{i + 1, j + 1, 2});
                sum += 2;
            }
        }
    }
    return sum;
}

void WriteMatrixToStream(const std::vector<std::vector<uint32_t>>& matrix, std::ostream& stream) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            stream << matrix[i][j] << " ";
        }
        stream << std::endl;
    }
}

void TGraph::PrintMinScheme() const {
    std::vector<std::vector<uint32_t>> newEdges;
    uint32_t sum = MST(newEdges);
    std::cout << newEdges.size() << ' ' << sum << std::endl;
    WriteMatrixToStream(newEdges, std::cout);
}

int main() {
    uint32_t n = 0, m = 0;
    std::cin >> n >> m;
    TGraph graph(n, m);
    graph.ReadFromStream(std::cin);
    graph.PrintMinScheme();
    return 0;
}

