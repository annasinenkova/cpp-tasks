#include <iostream>
#include <vector>
#include <algorithm>

enum { SIZE = 16 };

int32_t FindPos(const std::vector<int32_t>& vec, int32_t value) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] == value) {
            return i;
        }
    }
    return 0;
}

bool FillIJPos(std::vector<std::vector<int32_t>>& square, const std::vector<int32_t>& vec, std::vector<bool>& used, 
               int32_t sum, size_t i, size_t j, size_t start) 
{
    for (size_t k = start; k < SIZE; ++k) {
        if (!used[k]) {
            square[i][j] = vec[k];
            used[k] = true;
            if (i == 0) {
                start = k;
            } else if (j == 0) {
                start = FindPos(vec, square[i - 1][j]);
            } else {
                start = 1;
            }
            if (j == 2) {
                int32_t pos = FindPos(vec, sum - square[i][0] - square[i][1] - square[i][2]);
                if (!used[pos]) {
                    square[i][3] = vec[pos];
                    used[pos] = true;
                    if (i == 2) {
                        if (!used[FindPos(vec, sum - square[0][2] - square[1][2] - square[2][2])]) {
                            square[3][2] = vec[FindPos(vec, sum - square[0][2] - square[1][2] - square[2][2])];
                            square[3][3] = vec[FindPos(vec, sum - square[0][3] - square[1][3] - square[2][3])];
                            return true;
                        }
                    } else if (FillIJPos(square, vec, used, sum, i + 1, 0, start)) {
                        return true;
                    }
                    used[pos] = false;
                }
            } else if (i == 2) {
                int32_t pos = FindPos(vec, sum - square[0][j] - square[1][j] - square[2][j]);
                if (!used[pos]) {
                    square[3][j] = vec[pos];
                    used[pos] = true;
                    if (FillIJPos(square, vec, used, sum, i, j + 1, start)) {
                        return true;
                    }
                    used[pos] = false;
                }
            } else if (FillIJPos(square, vec, used, sum, i, j + 1, start)) {
                return true;
            }
            used[k] = false;
        }
    }
    return false;
}

bool FillSquareFromVector(std::vector<std::vector<int32_t>>& square, std::vector<int32_t>& vec) {
    int32_t sum = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        sum += vec[i];
    }
    if (sum % (SIZE >> 2) != 0) {
        return false;
    }
    sum = sum >> 2;
    std::sort(vec.begin(), vec.end());
    std::vector<bool> used(SIZE, false);
    square[0][0] = vec[0];
    used[0] = true;
    if (FillIJPos(square, vec, used, sum, 0, 1, 1)) {
        return true;
    }
    return false;
}

void WriteMatrixToStream(const std::vector<std::vector<int32_t>>& vec, std::ostream& stream) {
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            stream << vec[i][j] << " ";
        }
        stream << std::endl;
    }
}

void ReadVectorFromStream(std::vector<int32_t>& vec, std::istream& stream) {
    for (size_t i = 0; i < vec.size(); ++i) {
        stream >> vec[i];
    }
}

int32_t main() {
    std::vector<int32_t> vec(SIZE);
    ReadVectorFromStream(vec, std::cin);
    std::vector<std::vector<int32_t>> square(SIZE >> 2, std::vector<int32_t>(SIZE >> 2, 0));
    if (FillSquareFromVector(square, vec)) {
        WriteMatrixToStream(square, std::cout);
    } else {
        std::cout << "NO SOLUTION" << std::endl;
    }
    return 0;
}