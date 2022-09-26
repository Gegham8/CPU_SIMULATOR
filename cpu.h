#ifndef CPU_h
#define CPU_h
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class CPU {
private:
    typedef void(CPU::*chlp) (std::string&, std::string&);
    typedef bool(CPU::*ghlp) (std::string&, std::string&);
    std::ifstream file;
    std::map<std::string, int*>reg;
    std::map<std::string, chlp> ins;
    std::map<std::string, int> lable;
    std::map<std::string, ghlp> jmps;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;
    int r7;
    int r8;
    int r9;
    std::string cmp_1 = "";
    std::string cmp_2 = "";
    std::string cmp_3 = "";
private:
    void mov(std::string& str, std::string& str1);
    void add(std::string& str, std::string& str1);
    void mul(std::string& str, std::string& str1);
    void sub(std::string& str, std::string& str1);
    void div(std::string& str, std::string& str1);
    void _and(std::string& str, std::string& str1);
    void _or(std::string& str, std::string& str1);
    void _xor(std::string& str, std::string& str1);
    void _not(std::string& str, std::string& str1);
    void jmp(std::string& str, std::string& str1);
    void cmp(std::string& str, std::string& str1);
    bool equal(std::string& str, std::string& str1);
    bool nequal(std::string& str, std::string& str1);
    bool jz(std::string& str, std::string& str1);
    bool jnz(std::string& str, std::string& str1);
    bool jg(std::string& str, std::string& str1);
    bool jge(std::string& str, std::string& str1);
    bool jl(std::string& str, std::string& str1);
    bool jle(std::string& str, std::string& str1);
    void getlabel();
    void cut(std::string rhs);
    void make();
    bool check_rg(std::string);
    bool is_number(std::string);
public:
    void get_assm();
    void print();
    

public:
    CPU () : r1{}, r2{}, r3{}, r4{}, r5{}, r6{}, r7{}, r8{}, r9{}
    { make();}
};
#endif // CPU_h