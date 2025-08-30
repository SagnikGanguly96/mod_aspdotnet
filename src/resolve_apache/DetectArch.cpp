#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "Usage: DetectArch <path to httpd.exe>\n";
        return 1;
    }

    std::string path = std::string(argv[1]);
    std::ifstream file(path, std::ios::binary);
    if(!file) {
        std::cerr << "File not found\n";
        return 2;
    }

    // Read DOS header
    file.seekg(0x3C);
    uint32_t peOffset;
    file.read(reinterpret_cast<char*>(&peOffset), sizeof(peOffset));

    // Read PE signature
    file.seekg(peOffset + 4);
    uint16_t machine;
    file.read(reinterpret_cast<char*>(&machine), sizeof(machine));

    if(machine == 0x8664)
        std::cout << "x64\n";
    else if(machine == 0x14c)
        std::cout << "x86\n";
    else
        std::cout << "unknown\n";

    return 0;
}
