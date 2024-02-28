#include <iostream>
#include <vector>

void ReadVectorFromStream(std::vector<uint32_t>& vec, uint32_t size, std::istream& stream) {
    vec.resize(size);
    for (size_t i = 0; i < size; ++i) {
        stream >> vec[i];
    }
}

uint32_t FindMaxWiresLen(const std::vector<uint32_t>& wires, uint32_t k) {
    uint64_t totalLen = 0;
    for (size_t i = 0; i < wires.size(); ++i) {
        totalLen += wires[i];
    }
    uint32_t minLen = 1;
    uint32_t maxLen = totalLen / k;
    if (!maxLen) {
        return 0;
    }
    while (minLen < maxLen - 1) {
        uint32_t len = minLen + (maxLen - minLen) / 2;
        uint32_t count = 0;
        for (size_t i = 0; i < wires.size(); ++i) {
            count += wires[i] / len;
        }
        if (count < k) {
            maxLen = len;
        } else {
            minLen = len;
        }
    }
    uint32_t count = 0;
    for (size_t i = 0; i < wires.size(); ++i) {
        count += wires[i] / maxLen;
    }
    return count == k ? maxLen : minLen;
}

int main() {
    uint32_t n, k;
    std::cin >> n >> k;
    std::vector<uint32_t> wires;
    ReadVectorFromStream(wires, n, std::cin);
    std::cout << FindMaxWiresLen(wires, k) << std::endl;
    return 0;
}
