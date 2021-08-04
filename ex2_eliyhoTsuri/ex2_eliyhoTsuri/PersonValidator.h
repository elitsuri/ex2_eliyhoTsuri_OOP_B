#pragma once
#include "Validator.h"
template <typename T>
class PersonValidator : public Validator<T>
{
public:
	PersonValidator() {};
	~PersonValidator() {};
};