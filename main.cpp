#include <iostream>
#include <string>
using namespace std;

class Product{
public:
    virtual string getName() = 0;
    virtual ~Product() {}
};

class ConcreteProductA: public Product{
public:
    string getName() {return "ConcreteProductA";}
};

class ConcreteProductB: public Product{
public:
    string getName() {return "ConcreteProductB";}
};

class Creator{
public:
    virtual Product* factoryMethod() = 0;
};

class ConcreteCreatorA: public Creator{
public:
    Product* factoryMethod() {return new ConcreteProductA();}
};

class ConcreteCreatorB: public Creator{
public:
    Product* factoryMethod() {return new ConcreteProductB();}
};

int main()
{
    static const size_t count = 2;
    ConcreteCreatorA CreatorA;
    ConcreteCreatorB CreatorB;
    // An array of creators
    Creator*creators[count] = {&CreatorA, &CreatorB};
    // Iterate over creators and create products
    for(size_t i = 0; i<count; i++){
        Product* product=creators[i]->factoryMethod();
        cout << product->getName() << endl;
        delete product;
    }
    return 0;
}