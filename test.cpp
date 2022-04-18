#include <fstream>
#include <ios>

int main() {
    std::ofstream file("test.txt", std::ios::trunc);
    file << "yo";
}