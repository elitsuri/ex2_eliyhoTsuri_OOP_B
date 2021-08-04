#pragma once
#include "Validator.h"
template <class T>
class NumbersValidator :public Validator <T>
{
public:
	NumbersValidator() {};
	~NumbersValidator() {};
};
