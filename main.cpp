#include <iostream>
#include <functional>

#include "Algorithms.h"
#include "Async.h"
#include "MoveMyData.h"
#include "LambdaCalls.h"
#include "VaridicTemplates.h"
#include "AssociativeContainer.h"
#include "BinarySearchTree.h"
#include "Graph.h"
#include "MathFuncs.h"
#include "MoveSemantics.h"
#include "StringsRegEx.h"
#include "OpenClosedPrinciple.h"
#include "Graph2.h"

using namespace std;
namespace myfunc {
    std::function<void(void)> func = []() { cout << "Assigned Lamdba Call." << endl; };
}

int main()
{
    cout << "--------------------------Main--------------------------" << endl;

    demoGraph();

    runOCP();

    runStringAndRegEx();

    //performMoveSemantics();

    //callVariadicMins();

    asyncCall();

    Solution s;
    s.entityParser("&amp; is an HTML entity but &ambassador; is not.");

    /*cout << "\n\n==========================Graph & Tree=========================" << endl;
    BinarySearchTree bst;
    cout << "Inorder Traversal  : " ; bst.inorderPrint(bst.getHead()); cout << endl;
    cout << "Preorder Traversal : " ; bst.preOrder(bst.getHead()); cout << endl;

    Graph g{5, 6};
    g.createGraph();
    g.displayGraph();*/
    //s.entityParser("&lt;&apos;Y2#nh1hpJ&frasl;&amp;hmUp2Wndy &amp; &frasl;&apos;kCE6*LuWu &quot;&gt;");
    /*cout << "\n\n***************Variadic Template Calls***************" << endl;
    int a = 100;
    string str = "Hello";
    float f = 22.45;
    double d = 10000;
    print(a, str, f, d);

    cout << "\n\n***************Lambda Calls***************" << endl;
    lambdaCalls(myfunc::func);*/

    cout << "\n\n***************Algorithms***************" << endl;
    int target = 10;
    Algorithms algos;
    algos.init();
    cout << "Number of " << target << " within the vector are : " << algos.countInVector(target) << endl;
    cout << "There are " << algos.countWithCondition() << " Odds numbers in the vector." << endl;
    algos.employeesSalariesCategory();
    algos.findEmployeeWith10KSalary();
    cout << "The number " << target << " is " << algos.findInVector(target) << " in the vector." << endl;
    cout << "There is " << (algos.findWithCondition() ? "atleast one" : "no") << " even number in the vector." << endl;
    cout << "There is " << (algos.findWithCondition() ? "atleast one" : "no") << " odd number in the vector." << endl;
    vector<int> temp{1, 2, 3, 5};
    auto retVal = algos.findFirstOf(temp);
    cout << "Found " << retVal.second << endl;
    algos.stringReplace();

    /*algos.sortStruct();

    algos.shuffleVector();

    algos.compareEmployees();

    algos.copyAlgos();

    algos.transformAlgos();

    algos.reverseAlgos();

    algos.swapEmployees();

    algos.partitionBySalary();

    algos.splitString();

    algos.compressString();*/


    /*cout << "\n\n****************Testing Associative Containers***************" << endl;
    AssociativeContainer assoCont;
    //assoCont.populateSets();
    assoCont.populateStudentSet();
    assoCont.populateStudentMarksMap();
    //assoCont.populateEmployeeSet();

    cout << "\n\n****************Move Semantics***************" << endl;
    vector<int> v = { 10, 20, 30, 40, 50};
    auto m_data = MoveMyData(move(v));

    cout <<"Post Move Verification \n";
    cout <<"Checking Original Vector \n";
    for (auto a:v)
        cout << a << endl;

    cout <<"Checking Moved Vector inside m_data.vec \n";
    for( auto a:m_data.vec)
        cout << a << endl;

    auto m_data2 = MoveMyData(m_data.vec);
    cout <<"Checking copied Vector inside m_data2.vec \n";
    for( auto a:m_data2.vec)
        cout << a << endl;
    */

    /*cout << "\n\n****************Function Template with decltype******************" << endl;
    cout << "Greater between 5 and 5.00001 = " << maximum<int, float>(5, 5.00001) << endl;
    cout << "Greater between 5 and 4.99999 = " << maximum<int, float>(5, 4.99999) << endl;
    cout << "Greater between 4 and 4.00001 = " << maximum2<int, float>(4, 4.00001) << endl;
    cout << "Greater between 4 and 3.99999 = " << maximum3<int, float>(4, 3.99999) << endl;

    cout << "\n\n****************Prime Factors******************" << endl;
    cout << "Prime Factors of 20790 are : ";
    auto pf = primeFactors(20790);
    for( auto a_pf : pf)
        cout << a_pf << " ";
    cout << endl;

    cout << "\n\n**********************LCM**********************" << endl;
    cout << "LCM of 24 and 30 = " << lcm(24, 30) << endl;

    cout << "Is 29 prime ? " << boolalpha << isPrime(29) << endl;

    cout << "\n\n**********************GCD**********************" << endl;
    cout << "Enter the number of numbers you want to calculate GCD for : " ;
    int nos = 0;
    cin >> nos;
    vector<int> numbers;
    for( int i = 0; i < nos; ++i) {
        int number;
        cout << "Enter number " << i+1 << ": ";
        cin >> number;
        numbers.push_back(number);
    }
    cout << "GCD of ";
    for( auto num : numbers )
        cout << num << ", ";
    for( int i = 0; i < nos-1; ++i)
        numbers[i+1] = gcd_normal(numbers[i], numbers[i+1]);
    cout << " = " << numbers[nos-1] << endl;*/

    cout << "\n\n****************Base Conversion****************" << endl;
    int num, fromBase, toBase;
    cout << "Enter number    : "; cin >> num;
    cout << "Enter from base : "; cin >> fromBase;
    cout << "Enter to   base : "; cin >> toBase;
    baseN(num, fromBase, toBase);

    return 0;
}
