#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include <map>
#include <vector>

std::vector<unsigned char> readBytesFromFile(const std::string& filename, std::size_t start, std::size_t length) {
    std::vector<unsigned char> buffer(length);

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    file.seekg(start);
    file.read(reinterpret_cast<char*>(buffer.data()), length);

    buffer.resize(file.gcount()); // Resize buffer to actual number of bytes read
    return buffer;
}

std::string getOsAbiName(uint8_t osAbi) {
    static std::map<uint8_t, std::string> osAbiNames = {
        {0x00, "System V"},
        {0x01, "HP-UX"},
        {0x02, "NetBSD"},
        {0x03, "Linux"},
        {0x04, "GNU Hurd"},
        {0x06, "Solaris"},
        {0x07, "AIX (Monterey)"},
        {0x08, "IRIX"},
        {0x09, "FreeBSD"},
        {0x0A, "Tru64"},
        {0x0B, "Novell Modesto"},
        {0x0C, "OpenBSD"},
        {0x0D, "OpenVMS"},
        {0x0E, "NonStop Kernel"},
        {0x0F, "AROS"},
        {0x10, "FenixOS"},
        {0x11, "Nuxi CloudABI"},
        {0x12, "Stratus Technologies OpenVOS"}
    };

    auto it = osAbiNames.find(osAbi);
    if (it != osAbiNames.end()) {
        return it->second;
    } else {
        return "Unknown";
    }
}

std::string getIsaName(uint16_t isa) {
    static std::map<uint16_t, std::string> isaNames = {
        {0x00, "No specific instruction set"},
        {0x01, "AT&T WE 32100"},
        {0x02, "SPARC"},
        {0x03, "x86"},
        {0x04, "Motorola 68000 (M68k)"},
        {0x05, "Motorola 88000 (M88k)"},
        {0x06, "Intel MCU"},
        {0x07, "Intel 80860"},
        {0x08, "MIPS"},
        {0x09, "IBM System/370"},
        {0x0A, "MIPS RS3000 Little-endian"},
        {0x0B, "Reserved for future use"},
        {0x0C, "Reserved for future use"},
        {0x0D, "Reserved for future use"},
        {0x0E, "Reserved for future use"},
        {0x0F, "Hewlett-Packard PA-RISC"},
        {0x13, "Intel 80960"},
        {0x14, "PowerPC"},
        {0x15, "PowerPC (64-bit)"},
        {0x16, "S390, including S390x"},
        {0x17, "IBM SPU/SPC"},
        {0x18, "Reserved for future use"},
        {0x19, "Reserved for future use"},
        {0x1A, "Reserved for future use"},
        {0x1B, "Reserved for future use"},
        {0x1C, "Reserved for future use"},
        {0x1D, "Reserved for future use"},
        {0x1E, "Reserved for future use"},
        {0x1F, "Reserved for future use"},
        {0x20, "Reserved for future use"},
        {0x21, "Reserved for future use"},
        {0x22, "Reserved for future use"},
        {0x23, "Reserved for future use"},
        {0x24, "NEC V800"},
        {0x25, "Fujitsu FR20"},
        {0x26, "TRW RH-32"},
        {0x27, "Motorola RCE"},
        {0x28, "Arm (up to Armv7/AArch32)"},
        {0x29, "Digital Alpha"},
        {0x2A, "SuperH"},
        {0x2B, "SPARC Version 9"},
        {0x2C, "Siemens TriCore embedded processor"},
        {0x2D, "Argonaut RISC Core"},
        {0x2E, "Hitachi H8/300"},
        {0x2F, "Hitachi H8/300H"},
        {0x30, "Hitachi H8S"},
        {0x31, "Hitachi H8/500"},
        {0x32, "IA-64"},
        {0x33, "Stanford MIPS-X"},
        {0x34, "Motorola ColdFire"},
        {0x35, "Motorola M68HC12"},
        {0x36, "Fujitsu MMA Multimedia Accelerator"},
        {0x37, "Siemens PCP"},
        {0x38, "Sony nCPU embedded RISC processor"},
        {0x39, "Denso NDR1 microprocessor"},
        {0x3A, "Motorola Star*Core processor"},
        {0x3B, "Toyota ME16 processor"},
        {0x3C, "STMicroelectronics ST100 processor"},
        {0x3D, "Advanced Logic Corp. TinyJ embedded processor family"},
        {0x3E, "AMD x86-64"},
        {0x3F, "Sony DSP Processor"},
        {0x40, "Digital Equipment Corp. PDP-10"},
        {0x41, "Digital Equipment Corp. PDP-11"},
        {0x42, "Siemens FX66 microcontroller"},
        {0x43, "STMicroelectronics ST9+ 8/16 bit microcontroller"},
        {0x44, "STMicroelectronics ST7 8-bit microcontroller"},
        {0x45, "Motorola MC68HC16 Microcontroller"},
        {0x46, "Motorola MC68HC11 Microcontroller"},
        {0x47, "Motorola MC68HC08 Microcontroller"},
        {0x48, "Motorola MC68HC05 Microcontroller"},
        {0x49, "Silicon Graphics SVx"},
        {0x4A, "STMicroelectronics ST19 8-bit microcontroller"},
        {0x4B, "Digital VAX"},
        {0x4C, "Axis Communications 32-bit embedded processor"},
        {0x4D, "Infineon Technologies 32-bit embedded processor"},
        {0x4E, "Element 14 64-bit DSP Processor"},
        {0x4F, "LSI Logic 16-bit DSP Processor"},
        {0x8C, "TMS320C6000 Family"},
        {0xAF, "MCST Elbrus e2k"},
        {0xB7, "Arm 64-bits (Armv8/AArch64)"},
        {0xDC, "Zilog Z80"},
        {0xF3, "RISC-V"},
        {0xF7, "Berkeley Packet Filter"},
        {0x101, "WDC 65C816"},
        {0x102, "LoongArch"}
    };

    auto it = isaNames.find(isa);
    if (it != isaNames.end()) {
        return it->second;
    } else {
        return "Unknown ISA";
    }
}

void printSectionHeaders(const std::string& filename) {
    const std::size_t headerSize = 64; // Maximum size for both 32-bit and 64-bit ELF headers
    std::vector<unsigned char> header = readBytesFromFile(filename, 0, headerSize);

    uint8_t elfClass = header[4];
    uint64_t shOffset, shEntSize;
    uint16_t shNum, shStrIdx;

    if (elfClass == 1) { // 32-bit ELF header
        shOffset = *reinterpret_cast<uint32_t*>(&header[32]);
        shEntSize = *reinterpret_cast<uint16_t*>(&header[46]);
        shNum = *reinterpret_cast<uint16_t*>(&header[48]);
        shStrIdx = *reinterpret_cast<uint16_t*>(&header[50]);
    } else if (elfClass == 2) { // 64-bit ELF header
        shOffset = *reinterpret_cast<uint64_t*>(&header[40]);
        shEntSize = *reinterpret_cast<uint16_t*>(&header[58]);
        shNum = *reinterpret_cast<uint16_t*>(&header[60]);
        shStrIdx = *reinterpret_cast<uint16_t*>(&header[62]);
    } else {
        throw std::runtime_error("Unknown ELF class");
    }

    std::vector<unsigned char> sectionHeaders = readBytesFromFile(filename, shOffset, shNum * shEntSize);
    std::vector<unsigned char> strTable;

    // Read section header string table
    if (shStrIdx != 0) {
        uint64_t strTableOffset, strTableSize;
        if (elfClass == 1) {
            strTableOffset = *reinterpret_cast<uint32_t*>(&sectionHeaders[shStrIdx * shEntSize + 16]);
            strTableSize = *reinterpret_cast<uint32_t*>(&sectionHeaders[shStrIdx * shEntSize + 20]);
        } else {
            strTableOffset = *reinterpret_cast<uint64_t*>(&sectionHeaders[shStrIdx * shEntSize + 24]);
            strTableSize = *reinterpret_cast<uint64_t*>(&sectionHeaders[shStrIdx * shEntSize + 32]);
        }
        strTable = readBytesFromFile(filename, strTableOffset, strTableSize);
    }

    std::cout << "Section Headers:" << std::endl;

    for (int i = 0; i < shNum; ++i) {
        uint64_t shNameOffset;
        if (elfClass == 1) {
            shNameOffset = *reinterpret_cast<uint32_t*>(&sectionHeaders[i * shEntSize]);
        } else {
            shNameOffset = *reinterpret_cast<uint32_t*>(&sectionHeaders[i * shEntSize]);
        }

        std::string sectionName;
        if (shNameOffset < strTable.size()) {
            sectionName = reinterpret_cast<const char*>(&strTable[shNameOffset]);
            sectionName.erase(sectionName.find_last_not_of('\0') + 1); // Remove trailing zeros
        }

        // Print section header with proper alignment
        std::cout << "[" << std::setw(2) << std::right << i << "] ";
        if (!sectionName.empty()) {
            std::cout << std::left << sectionName;
        } else {
            std::cout << std::left << "Unknown";
        }
        std::cout << std::endl;
    }
}


struct ElfHeader {
    uint8_t e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

void printELFHeader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    ElfHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(ElfHeader));

    // Print magic number
    std::cout << "Magic: 0x";
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.e_ident[i]);
    }
    std::cout << " 'ELF'" << std::endl;

    // Print class (32-bit or 64-bit)
    std::cout << "Class: ";
    switch (header.e_ident[4]) {
        case 0x01: std::cout << "ELF32"; break;
        case 0x02: std::cout << "ELF64"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << std::endl;

    // Print data encoding (little endian or big endian)
    std::cout << "Data: ";
    switch (header.e_ident[5]) {
        case 0x01: std::cout << "Little Endian"; break;
        case 0x02: std::cout << "Big Endian"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << std::endl;

    // Print ELF version
    std::cout << "Version: " << std::dec << header.e_ident[6] << std::endl;

    // Print OS ABI
    std::cout << "OS/ABI: ";
    switch (header.e_ident[7]) {
        case 0x00: std::cout << "System V"; break;
        case 0x01: std::cout << "HP-UX"; break;
        case 0x02: std::cout << "NetBSD"; break;
        case 0x03: std::cout << "Linux"; break;
        case 0x04: std::cout << "GNU Hurd"; break;
        case 0x06: std::cout << "Solaris"; break;
        case 0x07: std::cout << "AIX (Monterey)"; break;
        case 0x08: std::cout << "IRIX"; break;
        case 0x09: std::cout << "FreeBSD"; break;
        case 0x0A: std::cout << "Tru64"; break;
        case 0x0B: std::cout << "Novell Modesto"; break;
        case 0x0C: std::cout << "OpenBSD"; break;
        case 0x0D: std::cout << "OpenVMS"; break;
        case 0x0E: std::cout << "NonStop Kernel"; break;
        case 0x0F: std::cout << "AROS"; break;
        case 0x10: std::cout << "FenixOS"; break;
        case 0x11: std::cout << "Nuxi CloudABI"; break;
        case 0x12: std::cout << "Stratus Technologies OpenVOS"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << " (" << static_cast<int>(header.e_ident[7]) << ")" << std::endl;

    // Print ABI version
    std::cout << "ABI Version: " << static_cast<int>(header.e_ident[8]) << std::endl;

    // Print type
    std::cout << "Type: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_type << std::endl;

    // Print ISA
    std::cout << "ISA: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_machine;
    std::cout << " (" << getIsaName(header.e_machine) << ")" << std::endl;

    // Print version
    std::cout << "Version: " << std::dec << header.e_version << std::endl;

    // Print entry point
    std::cout << "Entry point address: 0x" << std::hex << std::setw(16) << std::setfill('0') << header.e_entry << std::endl;

    // Print program header table offset
    std::cout << "Program header table offset: 0x" << std::hex << std::setw(16) << std::setfill('0') << header.e_phoff << std::endl;

    // Print section header table offset
    std::cout << "Section header table offset: 0x" << std::hex << std::setw(16) << std::setfill('0') << header.e_shoff << std::endl;

    // Print flags
    std::cout << "Flags: 0x" << std::hex << std::setw(8) << std::setfill('0') << header.e_flags << std::endl;

    // Print ELF header size
    std::cout << "ELF header size: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_ehsize << std::endl;

    // Print program header entry size
    std::cout << "Program header entry size: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_phentsize << std::endl;

    // Print number of program headers
    std::cout << "Number of program headers: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_phnum << std::endl;

    // Print section header entry size
    std::cout << "Section header entry size: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_shentsize << std::endl;

    // Print number of section headers
    std::cout << "Number of section headers: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_shnum << std::endl;

    // Print section header string table index
    std::cout << "Section header string table index: 0x" << std::hex << std::setw(4) << std::setfill('0') << header.e_shstrndx << std::endl;

    file.close();
}

struct ProgramHeader {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
};

void printProgramHeader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read ELF header to determine the size of program header entry
    uint16_t e_phentsize;
    file.seekg(0x36); // Position to e_phentsize in ELF header
    file.read(reinterpret_cast<char*>(&e_phentsize), sizeof(e_phentsize));

    // Seek to program header table offset
    uint64_t e_phoff;
    file.seekg(0x40); // Position to e_phoff in ELF header
    file.read(reinterpret_cast<char*>(&e_phoff), sizeof(e_phoff));

    // Calculate number of program header entries
    uint16_t e_phnum;
    file.seekg(0x3C); // Position to e_phnum in ELF header
    file.read(reinterpret_cast<char*>(&e_phnum), sizeof(e_phnum));

    // Seek to program header table
    file.seekg(e_phoff);

    // Read program headers
    for (int i = 0; i < e_phnum; ++i) {
        ProgramHeader phdr;

        file.read(reinterpret_cast<char*>(&phdr), e_phentsize);

        // Print program header entry
        std::cout << "Entry " << i + 1 << ":" << std::endl;
        std::cout << "  Type: ";
        switch (phdr.p_type) {
            case 0x00000000: std::cout << "PT_NULL"; break;
            case 0x00000001: std::cout << "PT_LOAD"; break;
            case 0x00000002: std::cout << "PT_DYNAMIC"; break;
            case 0x00000003: std::cout << "PT_INTERP"; break;
            case 0x00000004: std::cout << "PT_NOTE"; break;
            case 0x00000005: std::cout << "PT_SHLIB"; break;
            case 0x00000006: std::cout << "PT_PHDR"; break;
            case 0x00000007: std::cout << "PT_TLS"; break;
            case 0x60000000: std::cout << "PT_LOOS"; break;
            case 0x6FFFFFFF: std::cout << "PT_HIOS"; break;
            case 0x70000000: std::cout << "PT_LOPROC"; break;
            case 0x7FFFFFFF: std::cout << "PT_HIPROC"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << " (0x" << std::hex << std::setw(8) << std::setfill('0') << phdr.p_type << ")" << std::endl;

        std::cout << "  Flags: 0x" << std::hex << std::setw(8) << std::setfill('0') << phdr.p_flags << std::endl;
        std::cout << "  Offset: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_offset << std::endl;
        std::cout << "  Virtual Address: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_vaddr << std::endl;
        std::cout << "  Physical Address: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_paddr << std::endl;
        std::cout << "  File Size: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_filesz << std::endl;
        std::cout << "  Memory Size: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_memsz << std::endl;
        std::cout << "  Alignment: 0x" << std::hex << std::setw(16) << std::setfill('0') << phdr.p_align << std::endl;
    }

    file.close();
}


int main(int argc, char** argv) {

    bool pELfHeader = false;
    bool pProgramHeader = false;
    bool pSectionHeaders = false;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <options>" << std::endl;
        return 1;
    }

    if (std::strcmp(argv[2], "eps") == 0){
        pELfHeader = true;
        pProgramHeader = true;
        pSectionHeaders = true;
    } else if (std::strcmp(argv[2], "ep") == 0) {
        pELfHeader = true;
        pProgramHeader = true;
    } else if (std::strcmp(argv[2], "es") == 0) {
        pELfHeader = true;
        pSectionHeaders = true;
    } else if (std::strcmp(argv[2], "ps") == 0) {
        pProgramHeader = true;
        pSectionHeaders = true;
    } else if (std::strcmp(argv[2], "e") == 0) {
        pELfHeader = true;
    } else if (std::strcmp(argv[2], "p") == 0) {
        pProgramHeader = true;
    } else if (std::strcmp(argv[2], "s") == 0) {
        pSectionHeaders = true;
    }

    std::string filename = argv[1];

    std::vector<unsigned char> magic = readBytesFromFile(filename, 0, 3);

    std::cout << "ELF DUMP UTILITY: STEM UTILITIES [Copyright 2024-present Raphtik@GHG]" << std::endl;
    
    if (pELfHeader) {
        std::cout << "---------ELF HEADER---------" << std::endl;
        printELFHeader(filename);
    }
    if (pProgramHeader) {
        std::cout << "---------PROGRAM  HEADER---------" << std::endl;
        printProgramHeader(filename);
    }
    if (pSectionHeaders) {
        std::cout << "---------SECTION HEADERS---------" << std::endl;
        printSectionHeaders(filename);
    }
}