#include <iostream>

enum class Drink {
    whiskey = 1,
    vodka,
    cola,
    fanta,
    water,
    wine,
    rum,
    juice
};

struct Client {
    char name[32] = "";
    Drink preferdDrinks[8];
    int numberOfPreferedDrinks = 0;
};

bool doesLike(const Client& client, Drink drink) {
    for (size_t i = 0; i < client.numberOfPreferedDrinks; i++)
    {
        if (client.preferdDrinks[i] == drink)
        {
            return true;
        }
    }
    return false;
}

void like(Client& client, const Drink drink) {
    if (doesLike(client, drink))
    {
        return;
    }
    client.preferdDrinks[client.numberOfPreferedDrinks] = drink;
    ++client.numberOfPreferedDrinks;
}

void dislike(Client& client, const Drink drink) {
    if (!doesLike(client, drink))
    {
        return;
    }
    for (size_t i = 0; i < client.numberOfPreferedDrinks; i++)
    {
        if (client.preferdDrinks[i] == drink)
        {
            for (size_t j = i; j < client.numberOfPreferedDrinks - 1; j++)
            {
                client.preferdDrinks[j] = client.preferdDrinks[j + 1];
            }
            --client.numberOfPreferedDrinks;
            return;
        }
    }
}



void printPreferedDrinks(const Client& client) {
    for (size_t i = 0; i < client.numberOfPreferedDrinks; i++)
    {
        switch (client.preferdDrinks[i])
        {
        case Drink::cola:
            std::cout << "cola ";
            break;
        case Drink::whiskey:
            std::cout << "whiskey ";
            break;
        case Drink::vodka:
            std::cout << "vodka ";
            break;
        case Drink::fanta:
            std::cout << "fanta ";
            break;
        case Drink::water:
            std::cout << "water ";
            break;
        case Drink::rum:
            std::cout << "rum ";
            break;
        case Drink::wine:
            std::cout << "wine ";
            break;
        case Drink::juice:
            std::cout << "juice ";
            break;
        default:
            break;
        }
    }
    std::cout << std::endl;
}

int main()
{
    Client cl = { "Ivo", {Drink::cola, Drink::fanta, Drink::juice, Drink::water}, 4 };
    //std::cout << doesLike(cl, Drink::fanta);
    like(cl, Drink::rum);
    dislike(cl, Drink::fanta);
    printPreferedDrinks(cl);
}