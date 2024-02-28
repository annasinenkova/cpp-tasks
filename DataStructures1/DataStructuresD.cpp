#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

class TStringSet {
public:
    TStringSet() : HashTable(std::vector<std::list<std::string>>(SIZE)) {}
    void Add(const std::string& str);
    void Delete(const std::string& str);
    bool Find(const std::string& str) const;

private:
    uint32_t GenerateHash(const std::string& str) const;

private:
    enum { SIZE = 1'200'000 };

    std::vector<std::list<std::string>> HashTable;
};

uint32_t TStringSet::GenerateHash(const std::string& str) const {
    uint32_t polynMultValue = 31;
    uint64_t polynMult = 1;
    uint64_t hash = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        hash += polynMult * (str[i] - 'a' + 1);
        polynMult *= polynMultValue;
    }
    return hash % HashTable.size();
}

void TStringSet::Add(const std::string& str) {
    uint32_t hash = GenerateHash(str);
    auto itr = std::find(HashTable[hash].begin(), HashTable[hash].end(), str);
    if (itr != HashTable[hash].end()) {
        return;
    }
    HashTable[hash].push_back(str);
}

void TStringSet::Delete(const std::string& str) {
    uint32_t hash = GenerateHash(str);
    auto itr = std::find(HashTable[hash].begin(), HashTable[hash].end(), str);
    if (itr != HashTable[hash].end()) {
        HashTable[hash].erase(itr); 
    }
}

bool TStringSet::Find(const std::string& str) const {
    uint32_t hash = GenerateHash(str);
    auto itr = std::find(HashTable[hash].begin(), HashTable[hash].end(), str);
    if (itr != HashTable[hash].end()) {
        return true; 
    }
    return false;
}

int main() {
    TStringSet set;
    char operation;
    std::cin >> operation;
    while (operation != '#') {
        std::string str;
        std::cin >> str;
        if (operation == '+') {
            set.Add(str);
        } else if (operation == '-') {
            set.Delete(str);
        } else if (operation == '?') {
            std::cout << (set.Find(str) ? "YES" : "NO") << std::endl;
        }
        std::cin >> operation;
    }
    return 0;
}
