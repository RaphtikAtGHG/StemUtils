#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

void printHexAndAscii(const std::vector<unsigned char>& buffer) {
    std::size_t address = 0;
    const std::size_t bytesPerLine = 16;

    for (std::size_t i = 0; i < buffer.size(); i += bytesPerLine) {
        // Print address
        std::cout << std::setw(8) << std::setfill('0') << std::hex << address << " | ";
        address += bytesPerLine;

        // Print hex bytes
        for (std::size_t j = 0; j < bytesPerLine; ++j) {
            if (i + j < buffer.size()) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(buffer[i + j]) << " ";
            } else {
                std::cout << "   ";
            }
        }

        std::cout << "| ";

        // Print ASCII representation
        for (std::size_t j = 0; j < bytesPerLine; ++j) {
            if (i + j < buffer.size()) {
                unsigned char c = buffer[i + j];
                if (std::isprint(c)) {
                    std::cout << c;
                } else {
                    std::cout << ".";
                }
            }
        }

        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    // Read file into buffer
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Print hex and ASCII
    std::cout << "FILE DUMP UTILITY: STEM UTILITIES [Copyright 2024-present Raphtik@GHG]" << std::endl;
    printHexAndAscii(buffer);

    return 0;
}
