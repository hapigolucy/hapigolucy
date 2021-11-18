#include "MoveSemantics.h"

using namespace std;

String::String(const char* str)
{
    std::cout << "Created" << std::endl;
    mSize = strlen(str);
    mData = new char[mSize];
    memcpy(mData, str, mSize);
}

String::~String()
{
    delete[] mData;
}

String::String(const String& other)
{
    cout << "Copied" << endl;
    mSize = other.mSize;
    mData = new char[mSize];
    memcpy(mData, other.mData, mSize);
}

String::String(String&& other)
{
    cout << "Moved" << endl;
    mSize = other.mSize;
    mData = other.mData;

    other.mSize = 0;
    other.mData = nullptr;
}

String& String::operator=(const String& rhs)
{
    cout << "Copied through operator=" << endl;
    if (this == &rhs) // handle self assignment
        return *this;

    mSize = rhs.mSize;
    delete[] mData;
    mData = nullptr;
    mData = new char[mSize];
    memcpy(mData, rhs.mData, mSize);
    return *this;
}

void performMoveSemantics()
{
    cout << "Creating Entity : ";
    Entity entity("Aasim");
    entity.printName();
}
