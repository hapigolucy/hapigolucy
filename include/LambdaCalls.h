#include <iostream>
#include <functional>
using namespace std;

namespace{
    std::function<void(void)> func = []() { cout << "Emulating decltype for Lamdba Call." << endl; };
}

function<int(int)> lambdaRecursion() {
    function<int(int)> fct = [&fct](int a) {
        return (a==1 || a==0)? 1:a*fct(a-1);
    };
    return fct;
}

//TODO: Try to pass lambda to the function and call inside the function.
void lambdaCalls(decltype(func)){
    int n = 0;
    [](){ cout << "Direct Lambda Call." << endl; } ();
    auto l = []() { cout << "Assigned Lamdba Call." << endl; };
    l();
    func();
    function<int(int)> fact = lambdaRecursion();
    cout << "Implementing recursion through lambda (need to capture the lambda function via reference)." << endl;
    cout << "Enter a number : " ;
    cin >> n;
    cout << "Factorial of "<< n <<" is "<< fact(n);
    cout << "\n\n" << endl;
}
