#pragma once
// A class that represents a minimal value validator.
// It validates if a field value is not less than some minimal value.
// The type used as template parameter must implement > 
// operator and support to_string() function.
#include "NumbersValidator.h"
template <class T>
class MinValidator :public NumbersValidator<short>
{
public:
	MinValidator(std::string field)
	{
		m_error_validator = "Out of range \n";

		char year[1];
		year[0] = field[0];
		m_course = atoi(year);
		if (m_course >= 2)
			m_check_validator = true;
		else
			m_check_validator = false;
	}
	MinValidator(short min_course)
	{
		m_course = min_course;
	}
	virtual bool checkField(const short &min)const override
	{
		return (m_check_validator);
	}
	~MinValidator() {};
private:
	short m_course;
};