#include "MoveMyData.h"

MoveMyData::MoveMyData(const vector<int>& data) {
    cout << "Calling L-Value Constructor...\n";
    vec = data;
}

MoveMyData::MoveMyData(vector<int>&& data) {
    cout << "Calling R-Value Constructor...\n";
    vec = std::move(data);
}

MoveMyData::~MoveMyData() {
    //dtor
}
