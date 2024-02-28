#include <iostream>
#include <vector>

class TSegmTree {
private:
    struct TNode {
        TNode(int32_t max = 0, size_t idx = 0)
            : Max(max)
            , Idx(idx) {}

        int32_t Max;
        size_t Idx;
    };

public:
    TSegmTree(const std::vector<int32_t>& vec);
    size_t IdxMax(size_t from, size_t to) const;

private:
    TNode IdxMax(size_t idx, size_t left, size_t right, size_t from, size_t to) const;
    void Build(const std::vector<int32_t>& vec, size_t idx, size_t left, size_t right);

private:
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
        SegmTree[idx].Idx = left;
    } else {
        size_t mid = (left + right) >> 1;
        Build(vec, idx << 1, left, mid);
        Build(vec, (idx << 1) + 1, mid + 1, right);
        SegmTree[idx] = SegmTree[idx << 1].Max > SegmTree[(idx << 1) + 1].Max ? SegmTree[idx << 1] : SegmTree[(idx << 1) + 1];
    }
}

TSegmTree::TNode TSegmTree::IdxMax(size_t idx, size_t left, size_t right, size_t from, size_t to) const {
    if (from > to) {
        return TNode();
    }
    if (left == from && right == to) {
        return SegmTree[idx];
    }
    size_t mid = (left + right) >> 1;
    TNode leftMax = IdxMax(idx << 1, left, mid, from, std::min(to, mid));
    TNode rightMax = IdxMax((idx << 1) + 1, mid + 1, right, std::max(from, mid + 1), to);
    return leftMax.Max > rightMax.Max ? leftMax : rightMax;
}

size_t TSegmTree::IdxMax(size_t from, size_t to) const {
    return IdxMax(1, 0, Size - 1, from - 1, to - 1).Idx + 1;
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
    uint32_t k;
    std::cin >> k;
    for (size_t i = 0; i < k; ++i) {
        size_t from, to;
        std::cin >> from >> to;
        std::cout << segmTree.IdxMax(from, to) << " ";
    }
    std::cout << std::endl;
    return 0;
}