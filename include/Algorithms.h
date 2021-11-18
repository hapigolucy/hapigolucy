#pragma once
#include<deque>
#include<vector>
#include<list>
#include<string>
#include<algorithm>

#include "Employee.h"
#include <map>
#include <unordered_map>

using namespace std;

class Algorithms
{
public:
    Algorithms();
    virtual ~Algorithms();
    void init();
    Algorithms(const Algorithms& other);
    Algorithms& operator=(const Algorithms& other);

    void createUnorderedMap();

    int countInVector(int target);
    int countWithCondition();
    void employeesSalariesCategory();

    void findEmployeeWith10KSalary();
    std::string findInVector(int target);
    bool findWithCondition();
    bool findWithConditionNegated();
    std::pair<bool, int> findFirstOf(std::vector<int>& temp);
    void copyAlgos();

    void sortStruct();
    void shuffleVector();

    void compareEmployees();
    void transformAlgos();
    void reverseAlgos();

    void swapEmployees();
    void partitionBySalary();

    void splitString();

    void stringReplace();
    int compressString();

    friend ostream& operator<<(ostream& os, vector<int> vec);

protected:
    std::vector<int> integerVector;
    std::vector<Employee> employeeVector;

private:
};

class Solution {
    map<string, char> symbolMap ={ {"&quot;", '\"'}, {"&apos;", '\''}, {"&amp;", '&'}, {"&gt;", '>'}, {"&lt;", '<'}, {"&frasl;", '/'} };
public:
    void entityParser(string text) {
        cout << "\n\nInput  :" << text << " Size : " << text.length() << endl;
        string::iterator itBeg, itEnd;
        itBeg = find_if(begin(text), end(text), [](char c){  return c == '&'; });
        itEnd = find_if(itBeg, end(text), [](char c){  return c == ';'; });
        while(itEnd != end(text)) {
            itBeg = find(itBeg, end(text), '&');
            itEnd = find(itBeg, end(text), ';');
            string rep{itBeg, itEnd+1};
            string s;
            auto findMapIt = symbolMap.find({itBeg, itEnd+1});
            cout <<"Trying to find |" << rep << "|" << endl;
            if(findMapIt != symbolMap.end()) {
                s = findMapIt->second;
                string temp{itBeg, itEnd+1};
                text.replace(itBeg, itEnd+1, {findMapIt->second});
                cout << "Text   :" << text << " Size : " << text.length()<< " itBeg : " << *itBeg  << " at " << distance(begin(text), itBeg) << "|" << temp << "|" << s << "|" << endl;
                cout << "Text   :" << text << " Size : " << text.length()<< " itEnd : " << *itEnd  << " at " << distance(begin(text), itEnd) << "|" << temp << "|" << s << "|" << endl;
                --itEnd;
            }
            itBeg = itBeg + 1;
        }
        cout << "\n\nOutput : " << text << endl;
    }
};

class Solution3 {
    unordered_map<string, string> symbolMap ={ {"&quot;", "\""}, {"&apos;", "\'"}, {"&amp;", "&"}, {"&gt;", ">"}, {"&lt;", "<"}, {"&frasl;", "/"} };
public:
    void entityParser(string text) {
        cout << "Input  Text :" << text << endl;
        string result;
        int textSize = text.size();
        for(int i = 0; i < textSize; ++i)
        {
            bool flag = false;
            for( auto symbolPair : symbolMap )
            {
                string key = symbolPair.first;
                string value = symbolPair.second;
                if(i + key.size() - 1 < text.size())
                {
                    if(text.substr(i, key.size()) == key)
                    {
                        result += value;
                        i += key.size() - 1;
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag)
                 result += text[i];
        }
        cout << "Output Text :" << result << endl;

    }
};
