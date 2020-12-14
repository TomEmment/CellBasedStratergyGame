#pragma once
#include <iostream>
#include <string>
#include "Units.h"

using namespace std;

class Infantry : public Units
{
public:
	double AttackValues[3]={ 1,2,0.5 };
	int Priority[3]={1,0,2};
	Infantry();
};

