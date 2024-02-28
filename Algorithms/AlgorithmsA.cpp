#include <iostream>
#include <vector>

struct TObject {
    TObject(uint32_t cost = 0, uint32_t weight = 0)
        : Cost(cost)
        , Weight(weight) {}

    uint32_t Cost;
    uint32_t Weight;
};

uint32_t FindMaxCost(const std::vector<TObject>& objects, uint32_t maxWeight) {
    std::vector<std::vector<uint32_t>> cost(objects.size() + 1, std::vector<uint32_t>(maxWeight + 1, 0));
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = 1; j <= maxWeight; ++j) {
            if (j < objects[i].Weight) {
                cost[i + 1][j] = cost[i][j];
            } else {
                cost[i + 1][j] = std::max(cost[i][j], cost[i][j - objects[i].Weight] + objects[i].Cost);
            }
        }
    }
    return cost[objects.size()][maxWeight];
}

void ReadVectorFromStream(std::vector<TObject>& vec, std::istream& stream) {
    for (size_t i = 0; i < vec.size(); ++i) {
        stream >> vec[i].Weight;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        stream >> vec[i].Cost;
    }
}

int main() {
    uint32_t n, m;
    std::cin >> n >> m;
    std::vector<TObject> objects(n);
    ReadVectorFromStream(objects, std::cin);
    std::cout << FindMaxCost(objects, m) << std::endl;
    return 0;
}