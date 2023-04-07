#include <iostream>
#include <string>

class Customer
{
private:
    static int _s_count;
    static int _s_id_generator;
    std::string _name;
    std::string _location;
    int _age;
    double _business_done;
    int _transaction_count;
    int _id;

public:
    Customer(std::string name = "Max", int age = 42, std::string location = "Stuttgart")
    {
        this->_name = name;
        this->_location = location;
        this->_age = age;
        this->_business_done = 0;
        this->_transaction_count = 0;
        this->_id = _s_id_generator++;
        _s_count++;
    }

    ~Customer()
    {
        _s_count--;
    }

    void do_business(double amount)
    {
        this->_business_done += amount;
        this->_transaction_count++;
    }

    static int get_s_count()
    {
        return _s_count;
    }

    void print()
    {
        std::cout << "Kunde " << this->_name << " aus " << this->_location << " (ID = " << this->_id << ", " << this->_age << " Jahre) hatte " << this->_transaction_count << " Transaktion(en) und " << this->_business_done << " Euro Umsatz" << std::endl;
    }
};

int Customer::_s_count = 0;
int Customer::_s_id_generator = 1;

int main(int argc, char *argv[])
{
    Customer peter = Customer("Peter", 17, "Stuttgart");
    Customer simon = Customer("Simon", 23, "Heilbronn");
    peter.~Customer();
    Customer micheal = Customer("Michael", 21, "Karlsruhe");
    Customer claudia = Customer("Claudia", 30, "Nagold");
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
    simon.do_business(230);
    simon.do_business(400);
    claudia.do_business(1000);
    micheal.do_business(199);
    simon.do_business(3.99);
    simon.print();
    micheal.print();
    claudia.print();
    claudia.~Customer();
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
    return 0;
}
