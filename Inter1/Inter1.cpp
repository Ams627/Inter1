#include "stdafx.h"
#include <cstdint>
#include <stack>

union U
{
    unsigned char b[4];
    uint32_t u32;
    U(uint32_t u, bool swap = false) 
    {
        if (swap)
        {
            U temp(u);
            b[0] = temp.b[3];
            b[1] = temp.b[2];
            b[2] = temp.b[1];
            b[3] = temp.b[0];
        }
        else
        {
            u32 = u;
        }
    }
};

void PrintHexAsBytes1(uint32_t i)
{
    for (auto p = 0U; p < 8; ++p)
    {
        auto b = i >> 28;
        putchar(b < 10 ? b + '0' : b + 'A' - 10);
        i <<= 4;
    }
    putchar('\n');
}

void PrintHexAsBytes2(uint32_t i)
{
    U u(i, true);
    for (auto p : u.b)
    {
        auto n1 = p >> 4;
        auto n2 = p & 0xF;
        auto c1 = (n1 < 10) ? n1 + '0' : n1 - 10 + 'A';
        auto c2 = (n2 < 10) ? n2 + '0' : n2 - 10 + 'A';
        putchar(c1);
        putchar(c2);
    }
    putchar('\n');
}

void PrintHexAsBytes3(uint32_t i)
{
    std::stack<char> s;

    for (auto p = 0U; p < 8; ++p)
    {
        auto b = i & 0xF;
        s.push(b < 10 ? b + '0' : b + 'A' - 10);
        i >>= 4;
    }

    while (!s.empty())
    {
        putchar(s.top());
        s.pop();
    }
    putchar('\n');
}


#pragma optimize("", off)

int main()
{
    PrintHexAsBytes2(0x6278ABCE);
    PrintHexAsBytes1(0xDEADBEEF);
    PrintHexAsBytes3(0x62A19CDB);
    return 0;
}

