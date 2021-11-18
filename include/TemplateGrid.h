#pragma once

#include <iostream>
#include <vector>

template<typename T>
class TemplateGrid {
    public:
        static const size_t kDefaultWidth = 10;
        static const size_t kDefaultHeight = 10;

        explicit TemplateGrid(size_t width = kDefaultWidth, size_t height = kDefaultHeight);
        virtual ~TemplateGrid() = default;

        TemplateGrid(const TemplateGrid& other) = default;
        TemplateGrid<T>& operator=(const TemplateGrid& other) = default;

        TemplateGrid(TemplateGrid&& other) = default;
        TemplateGrid<T>& operator=(TemplateGrid&& other) = default;

        T& at(size_t x, size_t y);
//        const T& at(size_t x, size_t y) const;

        size_t getWidth()  { return mWidth; }
        size_t getHeight() { return mHeight; }

        std::vector<std::vector<T>> mCells;
    protected:

    private:
        size_t mWidth;
        size_t mHeight;
        void verifyCoordinate(size_t x, size_t y) const;
};

template<typename T>
TemplateGrid<T>::TemplateGrid(size_t width, size_t height)
    : mWidth(width), mHeight(height)
{
    mCells.resize(mWidth);
    for(auto& column : mCells) {
        column.resize(mHeight);
    }
}

template<typename T>
void TemplateGrid<T>::verifyCoordinate(size_t x, size_t y) const {
    if(x >= mWidth || y>=mHeight) {
        throw std::out_of_range("Invalid coordinates.");
    }
}

template<typename T>
T& TemplateGrid<T>::at(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return mCells[x][y];
}

//template<typename T>
//T& TemplateGrid<T>::at(size_t x, size_t y) {
//    return at(x, y);
//}
