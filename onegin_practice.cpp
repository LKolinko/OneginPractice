#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>
#include <random>

std::vector<std::pair<int, int>> sf, prt;
char* buffer;
char* buffer2;

void print_string(int ind) {
    for (int i = prt[ind].first; i <= prt[ind].second; ++i) {
        std::cout << buffer2[i];
    }
}

bool check(int ind, int jnd) {
    int size1 = -1, size2 = -1;
    int i = sf[ind].second, j = sf[jnd].second;
    while (buffer[i] != ' ') {
        if (buffer[i] != ' ' && buffer[i] != '\n') ++size1;
        --i;
    }
    while (buffer[j] != ' ') {
        if (buffer[j] != ' ' && buffer[j] != '\n') ++size2;
        --j;
    }
    // проверка по последниму слову
    if (size1 == size2) {
        bool flag = true;
        for (i = sf[ind].second - 1, j = sf[jnd].second - 1; i >= sf[ind].second - size1 - 1; --i, --j) {
            if (buffer[i] != buffer[j]) {
                flag = false;
                break;
            }

        }
        if (flag) return false;
    }
    // проверка на подстроку
    if (size1 != size2) {
        bool flag = true;
        for (i = sf[ind].second, j = sf[jnd].second; i >= sf[ind].second - size1 && j >= sf[jnd].second - size2; --i, --j) {
            if (buffer[i] != buffer[j]) {
                flag = false;
                break;
            }
        }
        if (flag) return false;
    }
    // проверка на последние 5 символов
    i = sf[ind].second - 1, j = sf[jnd].second;
    int cnt = 6;
    while (cnt) {
        if (buffer[i] == ' ' || buffer[i] == '\n') --i;
        if (buffer[j] == ' ' || buffer[j] == '\n') --j;
        if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[j] != ' ' && buffer[j] != '\n') {
            if (buffer[i] != buffer[j]) {
                return false;
            }
            --cnt;
            --i;
            --j;
        }
    }
    // проверка на ударение
    if (ind % 5 == jnd % 5) {
        return true;
    }
    return false;
}

int main() {
    std::setlocale(LC_ALL, "Rus");
    auto currentTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt(static_cast<unsigned int>(currentTime));
    std::ifstream inputFile("clear.txt", std::ios::binary);

    if (!inputFile) {
        std::cerr << "не удалось открыть файл" << std::endl;
        exit(1);
    }

    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    buffer = new char[fileSize];
    buffer2 = new char[fileSize];

    inputFile.read(buffer, fileSize);

    int start = 0, finish = 0;
    for (int i = 0; i <= fileSize; ++i) {
        if (buffer[i] == '\n') {
            sf.push_back({ start, finish });
            start = finish + 1;
        }
        ++finish;
    }

    std::ifstream inputFile2("Onegin.txt", std::ios::binary);

    if (!inputFile2) {
        std::cerr << "не та папка дебил" << std::endl;
        exit(1);
    }

    inputFile2.seekg(0, std::ios::end);
    std::streampos fileSize2 = inputFile2.tellg();
    inputFile2.seekg(0, std::ios::beg);

    buffer2 = new char[fileSize2];

    inputFile2.read(buffer2, fileSize2);

    start = 0, finish = 0;
    for (int i = 0; i <= fileSize2; ++i) {
        if (buffer2[i] == '\n') {
            prt.push_back({ start, finish });
            start = finish + 1;
        }
        ++finish;
    }

    std::vector<bool> used(sf.size(), false);
    std::vector<int> poem(14);
    for (int i = 0; i < 14; i += 2) {
        int ind = mt() % sf.size();
        while (used[ind]) ind = mt() % sf.size();
        used[ind] = true;
        int max = 0, res = -1;
        for (int j = 0; j < sf.size(); ++j) {
            if (ind != j && !used[j]) {
                if (check(ind, j)) {
                    res = j;
                    break;
                }
            }
        }
        if (res == -1) {
            i -= 2;
            continue;
        }
        poem[i] = ind;
        poem[i + 1] = res;
        used[res] = true;
    }

    print_string(poem[0]);
    print_string(poem[1]);
    print_string(poem[2]);
    print_string(poem[3]);
    std::cout << std::endl;
    print_string(poem[4]);
    print_string(poem[6]);
    print_string(poem[5]);
    print_string(poem[7]);
    std::cout << std::endl;
    print_string(poem[8]); 
    print_string(poem[10]); 
    print_string(poem[11]);
    print_string(poem[9]);
    std::cout << std::endl;
    print_string(poem[12]);
    print_string(poem[13]);

    delete[] buffer;
    delete[] buffer2;

    inputFile.close();

    return 0;
}
