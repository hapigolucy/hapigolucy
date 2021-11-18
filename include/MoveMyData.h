#pragma once
#include <vector>
#include <iostream>
using namespace std;

class MoveMyData
{
    public:
        MoveMyData(const vector<int>& data);
        MoveMyData(vector<int>&& data);
        virtual ~MoveMyData();
        vector<int> vec;

    protected:

    private:

};
