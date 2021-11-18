#pragma once
#include<iostream>
#include<cstring>

class String
{
    private:
        char* mData;
        int   mSize;

    public:
        String() = default;
        String(const char* str);
        ~String();
        String(const String& other);
        String(String&& other);
        String& operator=(const String& other);
        int getSize() { return mSize; }
        void print()
        {
            for(int i = 0; i < mSize; ++i)
                std::cout << mData[i];
            std::cout << std::endl;
        }
};

class Entity
{
    private:
        String mName;

    public:
        Entity() = default;
        Entity(const String& name):mName(name) {}
        Entity(String&& name):mName(name) {}
        Entity& operator=(const Entity& rhs) = default;
        void printName()
        {
            mName.print();
        }
};

void performMoveSemantics();
