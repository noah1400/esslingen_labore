#include <iostream>
#include <vector>
using namespace std;
//Interface IComponent
class IComponent
{
    public:
        virtual int getPrice() = 0;
        virtual void add(IComponent* component){};

};

//Class Product
class Product: public IComponent
{
    private:
        int price;
    public:
        Product(int price)
        {
            this->price = price;
        }
        int getPrice() override
        {
            return price;
        }
};

//Class Box
class Box: public IComponent
{
    public:
        vector<IComponent*> components;
        int getPrice() override
        {
            int price = 0;
            for(size_t i = 0; i < components.size(); i++)
            {
                price += components[i]->getPrice();
            }
            return price;
        }
        virtual void add(IComponent* component)
        {
            components.push_back(component);
        }
};

void ClientCode(IComponent *component)
{
    cout << "Price: " << component->getPrice() << endl;
}

int main(int argc, char* argv[]) {
    IComponent *product = new Product(10);
    cout << "Client: ein einfaches Produkt: " << endl;
    ClientCode(product);
    cout << endl << endl;

    IComponent *outerBox = new Box;
    IComponent *innerBox1 = new Box;

    IComponent *product1 = new Product(10);
    IComponent *product2 = new Product(5);
    IComponent *product3 = new Product(4);
    innerBox1->add(product1);
    innerBox1->add(product2);
    IComponent *innerBox2 = new Box;
    innerBox2->add(product3);
    outerBox->add(innerBox1);
    outerBox->add(innerBox2);
    cout << "Client: eine verschachtelte Box: " << endl;
    ClientCode(outerBox);
    cout << endl << endl;

    return 0;
}

