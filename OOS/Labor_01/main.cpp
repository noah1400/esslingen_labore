#include <string>
#include <ctime>
#include <iostream>

using namespace std;

// Aufzählungstyp für wählbare Objekte
// STEIN - 0, SCHERE - 1, PAPIER - 2
enum class Object
{
    ROCK,
    SCISSORS,
    PAPER
};

// Aufzählungstyp für mögliche Spielausgänge
enum class Result
{
    PLAYER_ONE_WINS,
    PLAYER_TWO_WINS,
    DRAW
};

// Struktur für einen Spieler bestehend aus Name und Wahl des Spielers
struct Player
{
    string name;
    Object choice;
};

// Name des Spielers eingeben
string insert_name()
{
    string name;
    cout << "Name des Spielers: ";
    getline(cin, name);
    return name;
}

Object determine_choice(string choice)
{
    if (choice.compare("CoderunnerTestValueROCK") == 0)
    {
        return Object::ROCK;
    }
    else if (choice.compare("CoderunnerTestValueSCISSORS") == 0)
    {
        return Object::SCISSORS;
    }
    else if (choice.compare("CoderunnerTestValuePAPER") == 0)
    {
        return Object::PAPER;
    }
    else
    {
        // Den Computer zufällig waehlen lassen.

        // HIER beantworten Sie folgende Fragen:
        // Wie funktioniert die funktion rand?
        // Die Funktion rand() gibt eine Zufallszahl zurück.

        // Was bewirkt die funktion srand?
        // Die Funktion srand() initialisiert den Zufallszahlengenerator.

        // Warum wird hier die Zeit (time) als Eingabe für die Funktion srand verwendet?
        // Die Funktion time() gibt die aktuelle Zeit in Sekunden zurück. 
        // Diese wird als Eingabe für srand() verwendet, damit die Zufallszahlengenerator nicht immer die gleiche Zufallszahl zurückgibt.
        
        // Warum wird hier modulo 3 verwendet?
        // Damit die Zufallszahl zwischen 0 und 2 liegt.

        srand(static_cast<int>(time(nullptr)));
        int choice = rand() % 3;
        return static_cast<Object>(choice);
    }
}

// Die Wahl von Stein etc. als String zurückgeben lassen
string get_name(Object object)
{
    switch (object)
    {
    case Object::ROCK:
        return "Stein";
    case Object::SCISSORS:
        return "Schere";
    case Object::PAPER:
        return "Papier";
    default:
        return "Unbekannt";
    }
}

// Einen Text mit dem Namen des Spielers und seiner Wahl ausgeben
void print_choice(Player player)
{
    cout << player.name << " hat das Objekt " << get_name(player.choice) << " gewählt" << endl;
}

// Die Wahl des Spielers abfragen
Object chose()
{
    int choice;
    do
    {
        cout << "Bitte Objektwahl eingeben (1 = Stein, 2 = Schere, 3 = Papier): ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return static_cast<Object>(choice - 1);

}

Result determine_result(Player player_1, Player player_2)
{

    int player_1_choice = static_cast<int>(player_1.choice);
    int player_2_choice = static_cast<int>(player_2.choice);

    if (player_1_choice == player_2_choice)
    {
        return Result::DRAW;
    }
    else if (player_1_choice == 0 && player_2_choice == 1)
    {
        return Result::PLAYER_ONE_WINS;
    }
    else if (player_1_choice == 1 && player_2_choice == 2)
    {
        return Result::PLAYER_ONE_WINS;
    }
    else if (player_1_choice == 2 && player_2_choice == 0)
    {
        return Result::PLAYER_ONE_WINS;
    }
    else
    {
        return Result::PLAYER_TWO_WINS;
    }
}

void print_result(Player player_1, Player player_2)
{

    Result result = determine_result(player_1, player_2);

    switch (result)
    {
    case Result::PLAYER_ONE_WINS:
        cout << "Spieler " << player_1.name << " hat gewonnen." << endl;
        break;
    case Result::PLAYER_TWO_WINS:
        cout << "Spieler " << player_2.name << " hat gewonnen." << endl;
        break;
    case Result::DRAW:
        cout << "Unentschieden" << endl;
        break;
    default:
        cout << "Unbekannt" << endl;
        break;
    }

}

int main(int argc, char *argv[])
{
    Player player_1, player_2;
    player_1.name = "Computer";
    player_2.name = insert_name();
    player_1.choice = determine_choice(player_2.name);
    cout << "Der Computer hat seine Wahl getroffen." << endl;
    player_2.choice = chose();
    print_choice(player_1);
    print_choice(player_2);
    print_result(player_1, player_2);

    return 0;
}

