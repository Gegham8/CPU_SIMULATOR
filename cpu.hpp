#include "cpu.h"
void CPU::make()
{
    reg["r1"] = &r1;
    reg["r2"] = &r2;
    reg["r3"] = &r3;
    reg["r4"] = &r4;
    reg["r5"] = &r5;
    reg["r6"] = &r6;
    reg["r7"] = &r7;
    reg["r8"] = &r8;
    reg["r9"] = &r9;
    ins["mov"] = &CPU::mov;
    ins["div"] = &CPU::div;
    ins["add"] = &CPU::add;
    ins["mul"] = &CPU::mul;
    ins["sub"] = &CPU::sub;
    ins["and"] = &CPU::_and;
    ins["or"] = &CPU::_or;
    ins["xor"] = &CPU::_xor;
    ins["not"] = &CPU::_not;
    ins["jmp"] = &CPU::jmp;
    ins["cmp"] = &CPU::cmp;
    jmps["je"] = &CPU::equal;
    jmps["jne"] = &CPU::nequal;
    jmps["jz"] = &CPU::jz;
    jmps["jnz"] = &CPU::jnz;
    jmps["jg"] = &CPU::jg;
    jmps["jge"] = &CPU::jge;
    jmps["jl"] = &CPU::jl;
    jmps["jle"] = &CPU::jle;
}

void CPU::cut(std::string rhs) 
{
    std::string operation = "";
    std::string reg = "";
    std::string src = "";
    int line = 0;
    int index = rhs.find(' ');
    if (rhs.find(',') != -1) {
        rhs.erase(rhs.begin() + rhs.find(','));
    }
    if (rhs.find(':') != -1) {
        rhs.erase(rhs.begin() + rhs.find(':'));
        lable[rhs] = this->file.tellg();
        return;
    }
    if (index == -1)
    {
        operation = rhs;
    }
    int space = 0;
    for (int i = 0; i < rhs.size(); ++i)
    {
        if (rhs[i] == ' ')
        {
            ++space;
        }
    }
    if (space == 1)
    {
        for (int i = 0; i < rhs.size(); ++i)
        {
            if (rhs[i] == ' ')
            {
                operation += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
            }
        }
        reg += rhs;
        cmp_3 = reg;
    }
    if (space == 2)
    {                                      
        for (int i = 0; i < rhs.size(); ++i)
        {
            if (rhs[i] == ' ')
            {
                operation += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
                reg += rhs.substr(0, rhs.find(' '));
                rhs.erase(rhs.begin(), rhs.begin() + rhs.find(' ') + 1);
            }
        }
        src += rhs;
        
    }
    if (operation[0] == 'j' && operation[1] != 'm')
    {
        (this->*jmps[operation])(cmp_1, cmp_2);
    }
    else if (operation.size() != 0)
    {
        (this->*ins[operation])(reg, src);
    }
}

void CPU::get_assm() 
{
    getlabel();
    std::string str1;
    file.open("assm.txt");
     if(file.is_open()) {
        while(getline(file, str1)) {
            if (str1 == "")
            {
                continue;
            }
            this->cut(str1);
        }
    } else {
        std::cout << "is not open";
    }
}

void CPU::mov(std::string& dest, std::string& src) 
{
 if (check_rg(dest)) {
   if(!check_rg(src) && is_number(src)) {
        *(reg[dest]) = stoi(src);
        return;
   }
   if (check_rg(src)) {
        *(reg[dest]) = *(reg[src]);
        return;
   }
}
    throw std::invalid_argument("Register is not found");
}
bool CPU::check_rg(std::string dest) 
{
    for(int i = 0; i < reg.size(); ++i) {
        if (reg.find(dest) == reg.end()) 
        {
             return false;
        }
    }
    return true;
}
bool CPU::is_number(std::string dest) 
{
    for(int i = 0; i < dest.size(); ++i) {
        if(!(dest[i] >= '0' && dest[i] <= '9')) {
            return false;
        }
    }
    return true;
}
void CPU::add(std::string& dest, std::string& src) 
{
    if (check_rg(dest)) {
        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) += stoi(src);
            return;
        }
        if (check_rg(src)) {
            *(reg[dest]) += *(reg[src]);
            return;
        } 
    }
    throw std::invalid_argument("Registr is not found");

}
void CPU::mul(std::string& dest, std::string& src) 
{
    if (check_rg(dest)) {

        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) *= stoi(src);
        }
        if (check_rg(src)) {
            *(reg[dest]) *= *(reg[src]);
        }
    }
    throw std::invalid_argument("Register is not found"); 
}
void CPU::_not(std::string& str, std::string& str1) 
{
     if (check_rg(str)) {
           *(reg[str]) = ~*(reg[str]);
            return;
        }
    throw std::logic_error("Eror");
}
void CPU::div(std::string& dest, std::string& src) 
{
    if (check_rg(dest))  {
        if(!check_rg(src) && is_number(src)) {
            *(reg[dest]) /= stoi(src);
        }
        if (check_rg(src)) {
            *(reg[dest]) /= *(reg[src]);
        }
    }
    throw std::invalid_argument("Register is not found");     
}
void CPU::sub(std::string& dest, std::string& src) 
{
    if(check_rg(dest)) {
        if(is_number(src)) {
            *(reg[dest]) -= stoi(src);
            return;
        }
        if (check_rg(src)) {
            *(reg[dest]) -= *(reg[src]);
            return;
        }
    }
    throw std::invalid_argument("Register is not found");  
}
void CPU::_and(std::string& dest, std::string& src) 
{
    if (check_rg(dest)) {
        if (!check_rg(src) && is_number(src)) {
            *(reg[dest]) &= stoi(src);
            return;
        }
        if (check_rg(src)) {
            *(reg[dest]) &= *(reg[src]);
            return;
        }
    }
    throw std::logic_error("Error");

}
void CPU::_or(std::string& str, std::string& str1) 
{
     if (check_rg(str)) {
        if (!check_rg(str1) && is_number(str1)) {
            *(reg[str]) |= stoi(str1);
            return;
        }
        if (check_rg(str1)) {
            *(reg[str]) |= *(reg[str1]);
            return;
        }
    }
    throw std::logic_error("Eror");
}
void CPU::_xor(std::string& str, std::string& str1) 
{
     if (check_rg(str)) {
        if (!check_rg(str1) && is_number(str1)) {
            *(reg[str]) ^= stoi(str1);
            return;
        }
        if (check_rg(str1)) {
            *(reg[str]) ^= *(reg[str1]);
            return;
        }
    }
    throw std::logic_error("Eror");
}
void CPU::jmp(std::string& dest, std::string& src) 
{
    this->file.seekg(this->lable[dest]);
    
}
void CPU::cmp(std::string& dest, std::string& src) 
{
        cmp_1 = dest;
        cmp_2 = src;
}
bool CPU::equal(std::string& dest, std::string& src) 
{
    if (check_rg(dest) && check_rg(src))
    {
        if((*reg[dest]) == (*reg[src]))
        {
            jmp(cmp_3, cmp_2);
        }
        return false;
    }
    else if (check_rg(dest) && is_number(src))
    {
        if((*reg[dest]) == stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
        return false;
    }
    return false;
   
}
bool CPU::nequal(std::string& dest, std::string& src)
{
    if (check_rg(dest) && check_rg(src))
    {
        if((*reg[dest]) != (*reg[src]))
        {
            jmp(cmp_3, cmp_2);
        }
        return false;
    }
    else if (check_rg(dest) && is_number(src))
    {
        if((*reg[dest]) != stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
void CPU::getlabel()
{
    std::string line;
    this->file.open("assm.txt");
    if (this->file.is_open())
    {
        while(!file.eof())
        {
            std::getline(this->file, line);
            if (line.find(":") != -1)
            {
                line.erase(line.begin() + line.find(":"));
                this->lable[line] = this->file.tellg();
            }
        }
    }
    file.close();
}
bool CPU::jz(std::string& dest, std::string& src)
{
    if (check_rg(dest) && (check_rg(src) || is_number(src)))
    {
        if (*reg[dest] ==  0)
        {
            jmp(cmp_3, cmp_2);
        }   
    }
    
    else
    {
        return false;
    }
    return false;
}
bool CPU::jnz(std::string& dest, std::string& src) 
{
    if (check_rg(dest) && (check_rg(src) || is_number(src)))
    {
        if (*reg[dest] !=  0)
        {
            jmp(cmp_3, cmp_2);
        }   
    }
    
    else
    {
        return false;
    }
    return false;
}
bool CPU::jg(std::string& dest, std::string& src)
{
    if (check_rg(dest) && (check_rg(src)))
    {
        if (*reg[dest] > *reg[src])
        {
            jmp(cmp_3, cmp_2);
        }
    }
    if (check_rg(dest) && is_number(src))
    {
        if (*reg[dest] > stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
bool CPU::jge(std::string& dest, std::string& src)
{
    if (check_rg(dest) && (check_rg(src)))
    {
        if (*reg[dest] >= *reg[src])
        {
            jmp(cmp_3, cmp_2);
        }
    }
    if (check_rg(dest) && is_number(src))
    {
        if (*reg[dest] >= stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
bool CPU::jl(std::string& dest, std::string& src)
{
    if (check_rg(dest) && (check_rg(src)))
    {
        if (*reg[dest] < *reg[src])
        {
            jmp(cmp_3, cmp_2);
        }
    }
    if (check_rg(dest) && is_number(src))
    {
        if (*reg[dest] < stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}
bool CPU::jle(std::string& dest, std::string& src)
{
if (check_rg(dest) && (check_rg(src)))
    {
        if (*reg[dest] <= *reg[src])
        {
            jmp(cmp_3, cmp_2);
        }
    }
    if (check_rg(dest) && is_number(src))
    {
        if (*reg[dest] <= stoi(src))
        {
            jmp(cmp_3, cmp_2);
        }
    }
    return false;
}

void CPU::print() {
   for (auto it : reg)
   {
        std::cout << it.first << " " << *it.second << std::endl;
   }
}
