#include <iostream>
#include <vector>

class TFenwickTree {
public:
    TFenwickTree(const std::vector<int32_t>& vec);
    void Update(size_t pos, int32_t value);
    int64_t Sum(size_t from, size_t to) const;

private:
    int64_t Sum(int32_t pos) const;

private:
    std::vector<int64_t> FenwTree;
};

TFenwickTree::TFenwickTree(const std::vector<int32_t>& vec)
    : FenwTree(std::vector<int64_t>(vec.size(), 0))
{
    for (size_t i = 0; i < vec.size(); ++i) {
        Update(i, vec[i]);
    }
}

void TFenwickTree::Update(size_t pos, int32_t value) {
    value -= Sum(pos, pos);
    while (pos < FenwTree.size()) {
        FenwTree[pos] += value;
        pos = pos | (pos + 1);
    }
}

int64_t TFenwickTree::Sum(int32_t pos) const {
    int64_t sum = 0;
    while (pos >= 0) {
        sum += FenwTree[pos];
        pos = (pos & (pos + 1)) - 1;
    }
    return sum;
}

int64_t TFenwickTree::Sum(size_t from, size_t to) const {
    return Sum(to) - Sum(from - 1);
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
    TFenwickTree fenwTree(vec);
    uint32_t m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        char operation;
        std::cin >> operation;
        if (operation == 's') {
            size_t from, to;
            std::cin >> from >> to;
            std::cout << fenwTree.Sum(from - 1, to - 1) << " ";
        } else if (operation == 'u') {
            size_t pos;
            int32_t value;
            std::cin >> pos >> value;
            fenwTree.Update(pos - 1, value);
        }
    }
    std::cout << std::endl;
    return 0;
}
