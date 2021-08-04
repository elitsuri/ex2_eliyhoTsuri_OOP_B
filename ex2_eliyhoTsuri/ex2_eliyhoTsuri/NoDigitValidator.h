#pragma once
// A class that represents a no-digit-characters validator.
// It validates that the field value contains no digits.
// Works only on std::string.
#include "PersonValidator.h"
#include <string>
class NoDigitValidator :public PersonValidator<std::string>
{
public:
	NoDigitValidator(const std::string &str)
		:m_str(str) 
	{
		m_error_validator = " Can't contain digits\n";

		m_check_validator = checkField(str);
	};
	NoDigitValidator() { m_error_validator = "Can't contain digits"; };
	~NoDigitValidator() {};
	virtual bool checkField(const std::string & name)const override
	{
		char c;
		unsigned i = 0;
		c = name[i];

		while (i < m_str.size())
		{
			if (isdigit(c))
				return false;
			i++;
			c = name[i];
		}
		return true;
	}
private:
	std::string m_str;
};