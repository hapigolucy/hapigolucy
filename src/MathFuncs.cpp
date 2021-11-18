#include "MathFuncs.h"

using namespace std;

void baseN(int num, int fromBase, int toBase) {
    int orig = num;
    int sum = 0, rem = 0;
    int i=1;
    cout << "Converting " << num << " from base " << fromBase << " to base " << toBase << endl;
    while(num > 0) {
        cout << endl;
        rem = num%toBase;    cout << "Remainder  = " << rem << endl;
        sum = sum + (rem*i); cout << "Number     = " << sum << endl;

        num = num/toBase;    cout << "Leftover   = " << num << endl;
        i *= fromBase;       cout << "Next Digit = " << i   << endl;
    }
    cout << "\n\n"
         << orig << " in base " << fromBase << " = "
         << sum << " in base " << toBase   << endl;
}

int gcd_recursive(int const a, int const b)
{
    return b == 0 ? a : gcd_recursive(b, a % b);
}

int gcd_normal(int a, int b)
{

    while(b!=0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm(int a, int b)
{
    int gcd = gcd_recursive(a, b);
    return gcd ? (a * (b/gcd)) : 0;
}

bool isPrime(int num)
{
    if( num <= 3 )
        return num > 1;
    else if ( num % 2 == 0 || num % 3 == 0 )
        return false;
    else
    {
        for(int i = 5; i * i <= num; i += 6)
        {
            if( num % i == 0 || num % (i+2) == 0)
                return false;
        }
        return true;
    }
}

vector<unsigned long long> primeFactors(unsigned long long n)
{
    vector<unsigned long long> primeFactors;
    while( n % 2 == 0) {
        primeFactors.push_back(2);
        n /= 2;
    }
    for(unsigned long long i = 3; i <= std::sqrt(n); i += 2)
    {
        while( n % i == 0){
            primeFactors.push_back(i);
            n /= i;
        }
    }
    if(n > 2)
        primeFactors.push_back(n);
    return primeFactors;
}
