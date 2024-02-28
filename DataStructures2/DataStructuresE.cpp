#include <iostream>
#include <vector>

class TSegmTree {
public:
    TSegmTree(const std::vector<int32_t>& vec);
    int32_t Max(size_t from, size_t to) const;
    void Add(size_t from, size_t to, int32_t value);

private:
    int32_t Max(size_t idx, size_t left, size_t right, size_t from, size_t to) const;
    void Add(size_t idx, size_t left, size_t right, size_t from, size_t to, int32_t value);
    void Build(const std::vector<int32_t>& vec, size_t idx, size_t left, size_t right);

private:
    struct TNode {
        TNode(int32_t max = 0)
            : Max(max)
            , Inc(0) {}

        int32_t Max;
        int32_t Inc;
    };

    size_t Size;
    std::vector<TNode> SegmTree;
};

TSegmTree::TSegmTree(const std::vector<int32_t>& vec)
    : Size(vec.size())
    , SegmTree(std::vector<TNode>(vec.size() << 2))
{
    if (Size) {
        Build(vec, 1, 0, Size - 1);
    }
}

void TSegmTree::Build(const std::vector<int32_t>& vec, size_t idx, size_t left, size_t right) {
    if (left == right) {
        SegmTree[idx].Max = vec[left];
    } else {
        size_t mid = (left + right) >> 1;
        Build(vec, idx << 1, left, mid);
        Build(vec, (idx << 1) + 1, mid + 1, right);
        SegmTree[idx].Max = std::max(SegmTree[idx << 1].Max, SegmTree[(idx << 1) + 1].Max);
    }
}

int32_t TSegmTree::Max(size_t idx, size_t left, size_t right, size_t from, size_t to) const {
    if (from > to) {
        return 0;
    }
    if (left == from && right == to) {
        return SegmTree[idx].Max;
    }
    size_t mid = (left + right) >> 1;
    return SegmTree[idx].Inc + std::max(Max(idx << 1, left, mid, from, std::min(to, mid)),
                                        Max((idx << 1) + 1, mid + 1, right, std::max(from, mid + 1), to));
}

int32_t TSegmTree::Max(size_t from, size_t to) const {
    return Max(1, 0, Size - 1, from - 1, to - 1);
}

void TSegmTree::Add(size_t idx, size_t left, size_t right, size_t from, size_t to, int32_t value) {
    if (from > to) {
        return;
    }
    if (left == from && right == to) {
        SegmTree[idx].Inc += value;
        SegmTree[idx].Max += value;
    } else {
        size_t mid = (left + right) >> 1;
        Add(idx << 1, left, mid, from, std::min(to, mid), value);
        Add((idx << 1) + 1, mid + 1, right, std::max(from, mid + 1), to, value);
        SegmTree[idx].Max = SegmTree[idx].Inc + std::max(SegmTree[idx << 1].Max, SegmTree[(idx << 1) + 1].Max);
    }
}

void TSegmTree::Add(size_t from, size_t to, int32_t value) {
    Add(1, 0, Size - 1, from - 1, to - 1, value);
}

void ReadVectorFromStream(std::vector<int32_t>& vec, size_t size, std::istream& stream) {
    vec.resize(size);
    for (size_t i = 0; i < size; ++i) {
        stream >> vec[i];
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    std::vector<int32_t> vec;
    ReadVectorFromStream(vec, n, std::cin);
    TSegmTree segmTree(vec);
    uint64_t m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        char operation;
        size_t from, to;
        std::cin >> operation >> from >> to;
        if (operation == 'm') {
            std::cout << segmTree.Max(from, to) << " ";
        } else if (operation == 'a') {
            int32_t value;
            std::cin >> value;
            segmTree.Add(from, to, value);
        }
    }
    std::cout << std::endl;
    return 0;
}