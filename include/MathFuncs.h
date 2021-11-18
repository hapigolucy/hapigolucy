#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include <math.h>

template<typename T1, typename T2>
auto maximum(T1 val1, T2 val2) -> decltype(val1 > val2 ? val1 : val2)
{
    return val1 < val2 ? val2 : val1;
}

template<typename T1, typename T2, typename RT = std::common_type_t<T1, T2>>
RT maximum2(T1 val1, T2 val2)
{
    return val1 < val2 ? val2 : val1;
}

template<typename T1, typename T2>
std::common_type_t<T1, T2> maximum3(T1 val1, T2 val2)
{
    return val1 < val2 ? val2 : val1;
}

void baseN(int num, int fromBase, int toBase);

int gcd_recursive(int const a, int const b);

int gcd_normal(int a, int b);

int lcm(int a, int b);

bool isPrime(int num);

std::vector<unsigned long long> primeFactors(unsigned long long n);
