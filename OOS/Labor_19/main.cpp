#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Gericht {
    protected:
        string name;
        vector<string> zutaten;
    public:
        Gericht(string name);
        void belegtMit(string zutat);
        virtual void zubereitung();
};

Gericht::Gericht(string name): name(name) {}
void Gericht::belegtMit(string zutat) {
    zutaten.push_back(zutat);
}
void Gericht::zubereitung() {
    for (string zutat : zutaten) {
        cout << "- " << zutat << endl;
    }
}

class Pizza: public Gericht {
    public:
        Pizza(string name);
        void belegtMit(string zutat);
        void zubereitung() override;
};

Pizza::Pizza(string name): Gericht(name) {}
void Pizza::belegtMit(string zutat) {
    Gericht::belegtMit(zutat);
}
void Pizza::zubereitung() {
    cout << "Pizza "<< name <<". Pizzaboden, belegt mit:" <<endl;
    Gericht::zubereitung();
}

class Burger: public Gericht {
    public:
        Burger(string name);
        void belegtMit(string zutat);
        void zubereitung() override;
};
Burger::Burger(string name): Gericht(name) {}
void Burger::belegtMit(string zutat){
    Gericht::belegtMit(zutat);
}
void Burger::zubereitung() {
    cout << name <<". Brötchen mit:" <<endl;
    Gericht::zubereitung();
}

int main(int argc, char* argv[])
{
    Pizza *mista = new Pizza("Mista");
    mista->belegtMit("Salami");
    mista->belegtMit("Pilzen");
    Gericht *hawaii = new Pizza("Hawaii");
    hawaii->belegtMit("Schinken");
    hawaii->belegtMit("Ananas");
    Burger *hamburger = new Burger("Hamburger");
    hamburger->belegtMit("Hackfleisch");
    Gericht *cheesburger = new Burger("Cheesburger");
    cheesburger->belegtMit("Hackfleisch");
    cheesburger->belegtMit("Käse");
    array<Gericht *, 4> speisekarte = {mista, hawaii, hamburger, cheesburger};
    for (Gericht *g : speisekarte)
    {
        g->zubereitung(); //*[1]
    }
    return 0;
}

