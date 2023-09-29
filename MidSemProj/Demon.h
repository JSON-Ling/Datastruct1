#pragma once
#include "Unit.h"
class Player;

#include <vector>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//demons can deal random damage to certain level

class Demon : public Unit
{
private:

public:
	Demon();
	Demon(string name, int health, int basedamage);
	~Demon();
	void printStatus();
};

