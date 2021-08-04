#pragma once
#include <string>
#include "BaseValidator.h"
template <typename T>
class Validator: public BaseValidator
{
public:
	Validator() {};
	virtual ~Validator() {};
	virtual bool checkField(const T &field)const = 0;
	virtual bool getCheckValidator() { return m_check_validator; };
};