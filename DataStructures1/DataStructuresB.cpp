#include <iostream>
#include <vector>
#include <stdexcept>

class TBinaryHeap {
public:
    TBinaryHeap(const std::vector<int32_t>& vec);
    int32_t GetMax() const;
    void Pop();

private:
    void Heapify(size_t i);

private:
    size_t HeapSize;
    std::vector<int32_t> Heap;
};

TBinaryHeap::TBinaryHeap(const std::vector<int32_t>& vec)
    : HeapSize(vec.size())
    , Heap(vec.begin(), vec.end()) 
{
    for (int i = HeapSize / 2; i >= 0; --i) {
        Heapify(i);
    }
}

void TBinaryHeap::Heapify(size_t i) {
    size_t currPos = i;
    while (true) {
        size_t nextPos = currPos;
        size_t left = 2 * currPos + 1;
        size_t right = 2 * currPos + 2;
        if (left < HeapSize && Heap[nextPos] < Heap[left]) {
            nextPos = left;
        }
        if (right < HeapSize && Heap[nextPos] < Heap[right]) {
            nextPos = right;
        }
        if (currPos == nextPos) {
            break;
        }
        std::swap(Heap[currPos], Heap[nextPos]);
        currPos = nextPos;
    }
}

int32_t TBinaryHeap::GetMax() const {
    if (!HeapSize) {
        throw std::runtime_error(nullptr);
    }
    return Heap[0];
}

void TBinaryHeap::Pop() {
    if (!HeapSize) {
        throw std::runtime_error(nullptr);
    }
    std::swap(Heap[0], Heap[--HeapSize]);
    Heapify(0);
}

void ReadVectorFromStream(std::vector<int32_t>& vec, uint32_t size, std::istream& stream) {
    vec.resize(size);
    for (size_t i = 0; i < size; ++i) {
        stream >> vec[i];
    }
}

void HeapSort(std::vector<int32_t>& vec) {
    TBinaryHeap heap(vec);
    for (int i = vec.size() - 1; i >= 0; --i) {
        vec[i] = heap.GetMax();
        heap.Pop();
    }
}

void WriteVectorToStream(const std::vector<int32_t>& vec, std::ostream& stream) {
    for (size_t i = 0; i < vec.size(); ++i) {
        stream << vec[i] << " ";
    }
    stream << std::endl;
}

int main() {
    uint32_t n;
    std::cin >> n;
    std::vector<int32_t> vec;
    ReadVectorFromStream(vec, n, std::cin);
    HeapSort(vec);
    WriteVectorToStream(vec, std::cout);
    return 0;
}
