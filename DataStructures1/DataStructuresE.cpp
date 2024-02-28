#include <iostream>
#include <algorithm>
#include <vector>

void ReadVectorFromStream(std::vector<uint32_t>& vec, uint32_t size, std::istream& stream) {
    vec.resize(size);
    for (size_t i = 0; i < size; ++i) {
        stream >> vec[i];
    }
}

uint32_t FindMinTotalLen(std::vector<uint32_t>& coord) {
    std::sort(coord.begin(), coord.end());
    if (coord.size() < 3) {
        return coord[1] - coord[0];
    }
    uint32_t totalLen1 = coord[1] - coord[0];
    uint32_t totalLen2 = totalLen1 + coord[2] - coord[1];
    for (size_t i = 2; i < coord.size() - 1; ++i) {
        uint32_t len = totalLen1;
        totalLen1 = totalLen2;
        totalLen2 = (len < totalLen2 ? len : totalLen2) + coord[i + 1] - coord[i];
    }
    return totalLen2;
}

int main() {
    uint32_t n;
    std::cin >> n;
    std::vector<uint32_t> coord;
    ReadVectorFromStream(coord, n, std::cin);
    std::cout << FindMinTotalLen(coord) << std::endl;
    return 0;
}
