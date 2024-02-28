#include <iostream>
#include <vector>

class TSegmTree {
public:
    TSegmTree(const std::vector<int32_t>& vec);
    int64_t Sum(size_t from, size_t to) const;
    void Update(size_t pos, int32_t value);

private:
    int64_t Sum(size_t idx, size_t left, size_t right, size_t from, size_t to) const;
    void Update(size_t idx, size_t left, size_t right, size_t pos, int32_t value);
    void Build(const std::vector<int32_t >& vec, size_t idx, size_t left, size_t right);

private:
    size_t Size;
    std::vector<int64_t> SegmTree;
};

TSegmTree::TSegmTree(const std::vector<int32_t>& vec)
    : Size(vec.size())
    , SegmTree(std::vector<int64_t>(vec.size() << 2, 0))
{
    if (Size) {
        Build(vec, 1, 0, Size - 1);
    }
}

void TSegmTree::Build(const std::vector<int32_t>& vec, size_t idx, size_t left, size_t right) {
    if (left == right) {
        SegmTree[idx] = vec[left];
    } else {
        size_t mid = (left + right) >> 1;
        Build(vec, idx << 1, left, mid);
        Build(vec, (idx << 1) + 1, mid + 1, right);
        SegmTree[idx] = SegmTree[idx << 1] + SegmTree[(idx << 1) + 1];
    }
}

int64_t TSegmTree::Sum(size_t idx, size_t left, size_t right, size_t from, size_t to) const {
    if (from > to) {
        return 0;
    }
    if (left == from && right == to) {
        return SegmTree[idx];
    }
    size_t mid = (left + right) >> 1;
    return Sum(idx << 1, left, mid, from, std::min(to, mid)) +
           Sum((idx << 1) + 1, mid + 1, right, std::max(from, mid + 1), to);
}

int64_t TSegmTree::Sum(size_t from, size_t to) const {
    return Sum(1, 0, Size - 1, from - 1, to - 1);
}

void TSegmTree::Update(size_t idx, size_t left, size_t right, size_t pos, int32_t value) {
    if (left == right) {
        SegmTree[idx] = value;
    } else {
        size_t mid = (left + right) >> 1;
        if (pos <= mid) {
            Update(idx << 1, left, mid, pos, value);
        } else {
            Update((idx << 1) + 1, mid + 1, right, pos, value);
        }
        SegmTree[idx] = SegmTree[idx << 1] + SegmTree[(idx << 1) + 1];
    }
}

void TSegmTree::Update(size_t pos, int32_t value) {
    Update(1, 0, Size - 1, pos - 1, value);
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
    uint32_t m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        char operation;
        std::cin >> operation;
        if (operation == 's') {
            size_t from, to;
            std::cin >> from >> to;
            std::cout << segmTree.Sum(from, to) << " ";
        } else if (operation == 'u') {
            size_t pos;
            int32_t value;
            std::cin >> pos >> value;
            segmTree.Update(pos, value);
        }
    }
    std::cout << std::endl;
    return 0;
}
