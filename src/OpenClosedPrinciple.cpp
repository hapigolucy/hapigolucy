#include "OpenClosedPrinciple.h"

using namespace std;

enum class Color {Red = 1, Green , Blue , Brown };
ostream& operator<<(ostream& os, const Color& color) {
    os << static_cast<underlying_type<Color>::type>(color);
    return os;
}

enum class Size  {Small = 1, Medium = 2, Large = 3};
ostream& operator<<(ostream& os, const Size& size) {
    os << static_cast<underlying_type<Size>::type>(size);
    return os;
}

struct Product
{
    string name;
    Color color;
    Size size;
};

template<typename T>
struct ISpecification
{
    virtual bool isSatisfied(T* item) = 0;
};

template<typename T>
struct IFilter
{
    virtual vector<T*> filter(vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product>
{
    using Items = vector<Product*>;
    Items filter(Items items, ISpecification<Product>& spec) override
    {
        Items result;
        for(auto& item : items)
            if(spec.isSatisfied(item))
                result.push_back(item);
        return result;
    }
};

struct ColorSpecification : ISpecification<Product>
{
    Color color;
    ColorSpecification(const Color color) : color{color}
    {}

    bool isSatisfied(Product* item) override {
        return item->color == color;
    }
};

void runOCP()
{
    Product apple       {"Apple",       Color::Green,   Size::Small};
    Product waterMelon  {"Water Melon", Color::Green,   Size::Large};
    Product chickoo     {"Chickoo",     Color::Brown,   Size::Small};
    Product strawberry  {"Strawberry",  Color::Red,     Size::Small};
    Product blueBerry   {"Blueberry",   Color::Blue,    Size::Small};

    vector<Product*> allProducts{&apple, &waterMelon, &chickoo};
    BetterFilter bf;
    ColorSpecification green(Color::Green);

    auto greenFruits = bf.filter(allProducts, green);
    cout << "\n\nGreen Fruits are : " << endl;
    for(auto& fruit : greenFruits) {
        cout << fruit->name << " " << fruit->color << " " << fruit->size << endl;
    }
}
