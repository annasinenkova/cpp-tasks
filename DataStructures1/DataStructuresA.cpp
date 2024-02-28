#include <iostream>

class TTree {
private:
    struct TNode {
        TNode(int32_t key = 0)
            : Left(nullptr)
            , Right(nullptr)
            , Key(key) {}

        TNode* Left;
        TNode* Right;
        int32_t Key;
    };

public:
    TTree()
        : Tree(nullptr) {}
    TTree(const TTree& tree) = delete;
    ~TTree();
    TTree& operator=(const TTree& tree) = delete;
    void Add(int32_t key);
    void DeleteTree();
    size_t GetTreeHeight() const;

private:
    void RecursiveAdd(TNode*& ptr, int32_t key);
    void RecursiveDelete(TNode* ptr);
    size_t RecursiveHeight(TNode* ptr) const;

private:
    TNode* Tree;
};

void TTree::Add(int32_t key) {
    RecursiveAdd(Tree, key);
}

void TTree::RecursiveAdd(TNode*& ptr, int32_t key) {
    if (!ptr) {
        ptr = new TNode(key);
    } else if (key < ptr->Key) {
        RecursiveAdd(ptr->Left, key);
    } else if (key > ptr->Key) {
        RecursiveAdd(ptr->Right, key);
    }
}

void TTree::DeleteTree() {
    RecursiveDelete(Tree);
    Tree = nullptr;
}

void TTree::RecursiveDelete(TNode* ptr) {
    if (ptr) {
        RecursiveDelete(ptr->Left);
        RecursiveDelete(ptr->Right);
        delete ptr;
    }
}

size_t TTree::GetTreeHeight() const {
    return RecursiveHeight(Tree);
}

size_t TTree::RecursiveHeight(TNode* ptr) const {
    if (!ptr) {
        return 0;
    }
    size_t leftHeight = RecursiveHeight(ptr->Left);
    size_t rightHeight = RecursiveHeight(ptr->Right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

TTree::~TTree() {
    DeleteTree();
}

int main() {
    TTree tree;
    int32_t value;
    std::cin >> value;
    while (value) {
        tree.Add(value);
        std::cin >> value;
    }
    std::cout << tree.GetTreeHeight() << std::endl;
    return 0;
}
