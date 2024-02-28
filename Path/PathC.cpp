#include <iostream>
#include <vector>

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
    for (uint32_t i = 0; i < Size; ++i) {
        Parent[i] = i;
    }
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
    if (Rank[reprO] > Rank[reprT]) {
        Parent[reprT] = reprO;
    } else {
        Parent[reprO] = reprT;
    }
    if (Rank[reprO] == Rank[reprT]) {
        ++Rank[reprT];
    }
}

uint32_t FindBridgesMinCount(uint32_t n, uint32_t m) {
    TDisjointSetUnion set(n);
    for (uint32_t i = 0; i < m; ++i) {
        uint32_t v1, v2;
        std::cin >> v1 >> v2;
        v1 = set.FindSet(v1);
        v2 = set.FindSet(v2);
        if (v1 != v2) {
            set.UnionSets(v1, v2);
        } else if (set.IsSetComplete()) {
            return i;
        }
    }
    return m;
}

int main() {
    uint32_t n, m;
    std::cin >> n >> m;
    std::cout << FindBridgesMinCount(n, m) << std::endl;
    return 0;
}

