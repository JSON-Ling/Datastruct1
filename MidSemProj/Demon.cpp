#include "Demon.h"
#include "Player.h"
Demon::Demon():Unit()
{
	
}

Demon::Demon(string name, int health, int basedamage):Unit(name,health,basedamage)
{
}

Demon::~Demon()
{

}

void Demon::printStatus()
{
	std::cout << "Health of Demon is: " << getHealth() << endl;
	std::cout << "Name of Demon is: " << getName() << endl;
	std::cout << "Base damage of Demon is: " << getBaseDamage() << endl;
}

