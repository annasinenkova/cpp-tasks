#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class TPointSet {
private:
    struct TPoint {
        bool operator==(TPoint point) {
            return x == point.x && y == point.y;
        }

        int x;
        int y;
    };
    
public:
    TPointSet()
        : Set(std::vector<TPoint>(0))
        , MinHull(std::vector<TPoint>(0)) {}
    void ReadFromStream(uint32_t size, std::istream& stream);
    void WriteMinHullToStream(std::ostream& stream);
    void FindMinHull();

private:
    bool Comp(TPoint a, TPoint b, TPoint c);
    int32_t VecProd(TPoint a, TPoint b, TPoint c);

private:
    std::vector<TPoint> Set;
    std::vector<TPoint> MinHull;
};

void TPointSet::ReadFromStream(uint32_t size, std::istream& stream) {
    Set.resize(size);
    for (size_t i = 0; i < size; ++i) {
        stream >> Set[i].x >> Set[i].y;
    }
}

void TPointSet::WriteMinHullToStream(std::ostream& stream) {
    FindMinHull();
    stream << MinHull.size() << std::endl;
    if (Set.size() % 2) {
        for (int i = MinHull.size() - 1; i >= 0 ; --i) {
            stream << MinHull[i].x << " " << MinHull[i].y << std::endl;
        }
    } else {
        for (size_t i = 0; i < MinHull.size(); ++i) {
            stream << MinHull[i].x << " " << MinHull[i].y << std::endl;
        }
    }
}

int32_t TPointSet::VecProd(TPoint a, TPoint b, TPoint c) {
    return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
}

bool TPointSet::Comp(TPoint a, TPoint b, TPoint c) {
    int32_t vecProd = VecProd(a, b, c);
    if (!vecProd) {
        return b.x < c.x || (b.x == c.x && b.y < c.y);
    }
    return vecProd > 0;
}

void TPointSet::FindMinHull() {
    std::vector<TPoint> set(Set.begin(), Set.end());
    for (size_t i = 0; i < set.size(); ++i) {
        if (set[i].x < set[0].x || (set[i].x == set[0].x && set[i].y < set[0].y)) {
            std::swap(set[0], set[i]);
        }
    }
    using namespace std::placeholders;
    std::sort(++set.begin(), set.end(), std::bind(&TPointSet::Comp, this, set[0], _1, _2));
    set.resize(std::unique(set.begin(), set.end()) - set.begin());
    if (set.size() < 3) {
        MinHull = set;
        return;
    }
    MinHull.push_back(set[0]);
    MinHull.push_back(set[1]);
    for (size_t i = 2; i < set.size(); ++i) {
        while (MinHull.size() >= 2 && VecProd(MinHull[MinHull.size() - 2], MinHull[MinHull.size() - 1], set[i]) <= 0 ) {
            MinHull.pop_back();
        }
        MinHull.push_back(set[i]);
    }
    if (MinHull.size() > 2 && VecProd(MinHull[MinHull.size() - 2], MinHull[MinHull.size() - 1], set[0]) == 0) {
        MinHull.pop_back();
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    TPointSet set;
    set.ReadFromStream(n, std::cin);
    set.WriteMinHullToStream(std::cout);
    return 0;
}
