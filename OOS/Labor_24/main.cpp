#include <vector>
#include <string>
#include <iostream>
using namespace std;

//Observer Interface Subscriber
class ISubscriber
{
    public:
        virtual void update(string) = 0;
};

class Store
{
    private:
        vector<ISubscriber*> subscribers;
        string mainState;
    public:
        void subscribe(ISubscriber* subscriber)
        {
            subscribers.push_back(subscriber);
        }
        void unsubscribe(ISubscriber* subscriber)
        {
            for (size_t i = 0; i < subscribers.size(); i++)
            {
                if (subscribers[i] == subscriber)
                {
                    subscribers.erase(subscribers.begin() + i);
                }
            }
        }
        void notify()
        {
            for(size_t i = 0; i < subscribers.size(); i++)
            {
                subscribers[i]->update(mainState);
            }
        }
        void deliverGoods()
        {
            mainState = "IPhone verfügbar";
            notify();
        }
        void sellGoods()
        {
            mainState = "IPhone nicht mehr verfügbar";
            notify();
        }
};

class Customer: public ISubscriber
{
    private:
        static int ID;
        const int id;
    public:
        Customer(): id(ID++)
        {}
        void update(string state)
        {
            cout << "Customer "<<id<<": neue Nachricht verfügbar --> "<<state<<endl;
        }
};
int Customer::ID = 1;

void ClientCode()
{
    Store *store = new Store;
    Customer *customer1 = new Customer();
    store->subscribe(customer1);
    Customer *customer2 = new Customer();
    store->subscribe(customer2);
    Customer *customer3 = new Customer();
    store->subscribe(customer3);
    Customer *customer4;
    Customer *customer5;
    store->deliverGoods();
    store->unsubscribe(customer3);
    store->sellGoods();
    customer4 = new Customer();
    store->subscribe(customer4);
    store->unsubscribe(customer2);
    customer5 = new Customer();
    store->subscribe(customer5);
    store->deliverGoods();
    store->unsubscribe(customer5);
    store->unsubscribe(customer4);
    store->unsubscribe(customer1);
}
int main(int argc, char* argv[]) {
    ClientCode();
    return 0;
}

