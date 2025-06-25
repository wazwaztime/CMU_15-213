#include <bits/stdc++.h>

std::vector<std::string> readfile(std::ifstream &file) {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

size_t bitsize(std::string s) {
    if (s == "rax" || s == "rbx" || s == "rcx" || s == "rdx" ||
        s == "rsi" || s == "rdi" || s == "r8" || s == "r9" ||
        s == "r10" || s == "r11" || s == "r12" || s == "r13" ||
        s == "r14" || s == "r15" || s == "rsp" || s == "rbp" || s == "rip") {
        return 8;
    }
    if (s == "eax" || s == "ebx" || s == "ecx" || s == "edx" ||
        s == "esi" || s == "edi" || s == "r8d" || s == "r9d" ||
        s == "r10d" || s == "r11d" || s == "r12d" || s == "r13d" ||
        s == "r14d" || s == "r15d" || s == "esp" || s == "ebp") {
        return 4;
    }
    if (s == "ax" || s == "bx" || s == "cx" || s == "dx" ||
        s == "si" || s == "di" || s == "r8w" || s == "r9w" ||
        s == "r10w" || s == "r11w" || s == "r12w" || s == "r13w" ||
        s == "r14w" || s == "r15w" || s == "sp" || s == "bp") {
        return 2;
    }
    if (s == "al" || s == "bl" || s == "cl" || s == "dl" ||
        s == "sil" || s == "dil" || s == "r8b" || s == "r9b" ||
        s == "r10b" || s == "r11b" || s == "r12b" || s == "r13b" ||
        s == "r14b" || s == "r15b" || s == "spl" || s == "bpl") {
        return 1;
    }
    return 0; 
}

std::string Reg(std::string reg) {
    if (reg == "rax" || reg == "eax" || reg == "ax" || reg == "al") return "rax";
    if (reg == "rbx" || reg == "ebx" || reg == "bx" || reg == "bl") return "rbx";
    if (reg == "rcx" || reg == "ecx" || reg == "cx" || reg == "cl") return "rcx";
    if (reg == "rdx" || reg == "edx" || reg == "dx" || reg == "dl") return "rdx";
    if (reg == "rsi" || reg == "esi" || reg == "si" || reg == "sil") return "rsi";
    if (reg == "rdi" || reg == "edi" || reg == "di" || reg == "dil") return "rdi";
    if (reg == "r8" || reg == "r8d" || reg == "r8w" || reg == "r8b") return "r8";
    if (reg == "r9" || reg == "r9d" || reg == "r9w" || reg == "r9b") return "r9";
    if (reg == "r10" || reg == "r10d" || reg == "r10w" || reg == "r10b") return "r10"; 
    if (reg == "r11" || reg == "r11d" || reg == "r11w" || reg == "r11b") return "r11";
    if (reg == "r12" || reg == "r12d" || reg == "r12w" || reg == "r12b") return "r12";
    if (reg == "r13" || reg == "r13d" || reg == "r13w" || reg == "r13b") return "r13";
    if (reg == "r14" || reg == "r14d" || reg == "r14w" || reg == "r14b") return "r14";
    if (reg == "r15" || reg == "r15d" || reg == "r15w" || reg == "r15b") return "r15";
    if (reg == "rsp" || reg == "esp" || reg == "sp" || reg == "spl") return "rsp";
    if (reg == "rbp" || reg == "ebp" || reg == "bp" || reg == "bpl") return "rbp";
    return reg; // Return the original if no match found
}

std::map<std::string, size_t> reg;

size_t &getreg(std::string s) {
    s = Reg(s);
    if (reg.find(s) == reg.end()) {
        reg[s] = 0;
    }
    return reg[s];
}

unsigned char Mem_array[0x1000000];
unsigned char &mem(size_t address) {
    if (address >= sizeof(Mem_array)) {
        std::cerr << "Memory access out of bounds: " << address << std::endl;
        exit(1);
    }
    return Mem_array[address];
}

void push(std::string s) {
    size_t& address = getreg("rsp");
    size_t size = bitsize(s);
    if (size == 0) {
        std::cerr << "Invalid register: " << s << std::endl;
        exit(1);
    }
    address -= 8;
    size_t value = getreg(s) & ((1ULL << (size * 8)) - 1);
    for (size_t i = 0; i < size; ++i) {
        mem(address + i) = (value) & 0xFF;
        value >>= 8;
    }
}

void pop(std::string s) {
    size_t& address = getreg("rsp");
    size_t size = bitsize(s);
    if (size == 0) {
        std::cerr << "Invalid register: " << s << std::endl;
        exit(1);
    }
    size_t value = 0;
    for (size_t i = 0; i < size; ++i) {
        value |= static_cast<size_t>(mem(address + i)) << (i * 8);
    }
    getreg(s) = value;
    address += 8;
}

void mov(std::string src, std::string dest) {
    size_t size = bitsize(dest);
    if (size == 0) {
        std::cerr << "Invalid destination register: " << dest << std::endl;
        exit(1);
    }
    
}

void convert(std::string s) {
    std::istringstream ss(s);
    size_t address;
    if (s[0] == '0') {
        //function signature
        std::string func_name;
        ss >> std::hex >> address >> func_name;
        //drop from "<func_name>:"
        func_name = func_name.substr(1, func_name.size() - 3);
        std::cerr << address << " : " << func_name << std::endl;
    }
    return;
}

int main() {
    getreg("rsp") = 0x10000;
    std::ifstream file("test.asm");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::vector<std::string> lines = readfile(file);
    file.close();
    for (const auto &line : lines) {
        convert(line);
    }
}