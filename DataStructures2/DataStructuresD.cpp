#include <iostream>

class TTreap {
private:
    struct TNode {
        TNode(int32_t key = 0)
            : Priority(rand())
            , Key(key)
            , Left(nullptr)
            , Right(nullptr) {}

        int32_t Priority;
        int32_t Key;
        TNode* Left;
        TNode* Right;
    };

public:
    TTreap()
        : Treap(nullptr) {}
    TTreap(const TTreap& treap) = delete;
    ~TTreap();
    TTreap& operator=(const TTreap& treap) = delete;
    void Clear();
    void Add(int32_t key);
    bool Find(int32_t key) const;
    int32_t Next(int32_t key);

private:
    void Clear(TNode* ptr);
    void Add(TNode* newNode, TNode*& ptr);
    bool Find(int32_t key, TNode* ptr) const;
    TNode* Merge(TNode* ptr1, TNode* ptr2);
    void Split(int32_t key, TNode* ptr, TNode*& ptr1, TNode*& ptr2);

private:
    TNode* Treap;
};

void TTreap::Split(int32_t key, TNode* ptr, TNode*& ptr1, TNode*& ptr2) {
    if (!ptr) {
        ptr1 = nullptr;
        ptr2 = nullptr;
    } else if (ptr->Key < key) {
        Split(key, ptr->Right, ptr->Right, ptr2);
        ptr1 = ptr;
    } else {
        Split(key, ptr->Left, ptr1, ptr->Left);
        ptr2 = ptr;
    }
}

TTreap::TNode* TTreap::Merge(TNode* ptr1, TNode* ptr2) {
    if (!ptr1 || !ptr2) {
        return ptr1 ? ptr1 : ptr2;
    } else if (ptr2->Priority < ptr1->Priority) {
        ptr1->Right = Merge(ptr1->Right, ptr2);
        return ptr1;
    } else {
        ptr2->Left = Merge(ptr1, ptr2->Left);
        return ptr2;
    }
}

bool TTreap::Find(int32_t key, TNode* ptr) const {
    if (!ptr) {
        return false;
    } else if (key == ptr->Key) {
        return true;
    } else if (key < ptr->Key) {
        return Find(key, ptr->Left);
    } else {
        return Find(key, ptr->Right);
    }
}

bool TTreap::Find(int32_t key) const {
    return Find(key, Treap);
}

void TTreap::Add(TNode* newNode, TNode*& ptr) {
    if (!ptr) {
        ptr = newNode;
    } else if (ptr->Priority < newNode->Priority) {
        Split(newNode->Key, ptr, newNode->Left, newNode->Right);
        ptr = newNode;
    } else if (newNode->Key < ptr->Key) {
        Add(newNode, ptr->Left);
    } else {
        Add(newNode, ptr->Right);
    }
}

void TTreap::Add(int32_t key) {
    if (!Find(key)) {
        TNode* newNode = new TNode(key);
        Add(newNode, Treap);
    }
}

int32_t TTreap::Next(int32_t key) {
    TNode* ptr1 = nullptr;
    TNode* ptr2 = nullptr;
    Split(key, Treap, ptr1, ptr2);
    int32_t next = -1;
    if (ptr2) {
        TNode* ptr = ptr2;
        while (ptr->Left) {
            ptr = ptr->Left;
        }
        next = ptr->Key;
    }
    Treap = Merge(ptr1, ptr2);
    return next;
}

void TTreap::Clear(TNode* ptr) {
    if (ptr) {
        Clear(ptr->Left);
        Clear(ptr->Right);
        delete ptr;
    }
}

void TTreap::Clear() {
    Clear(Treap);
    Treap = nullptr;
}

TTreap::~TTreap() {
    Clear();
}

enum { MAX = 1'000'000'000 };

int main() {
    TTreap treap;
    uint32_t n = 0;
    std::cin >> n;
    int32_t y = 0;
    for (size_t j = 0; j < n; ++j) {
        char operation;
        int32_t i;
        std::cin >> operation >> i;
        if (operation == '+') {
            treap.Add((i + y) % MAX);
            y = 0;
        } else if (operation == '?') {
            y = treap.Next(i);
            std::cout << y << std::endl;
        }
    }
    return 0;
}
