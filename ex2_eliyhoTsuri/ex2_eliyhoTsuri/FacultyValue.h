#pragma once
// A class that represents the value use for faculty field.
// The class must override the << and >> operators.
// >> operator reads an int and << operator prints faculty name if the value is
// valid and if not - the number.
#include "PersonValidator.h"
class FacultyValue :public PersonValidator<std::string>
{
public:
	FacultyValue() {};
	FacultyValue(std::string faculty) 
	{
		m_error_validator = "Out of range \n";
		if (faculty == "1" || faculty == "2" || faculty == "3")
			m_check_validator = true;
		else
			m_check_validator = false;
	};
	FacultyValue(int range1,int range2)
		:m_range1(range1),m_range2(range2) {};
	virtual bool checkField(const std::string &str)const override
	{
		return m_check_validator;
	}

private: 
	int m_range1;
	int m_range2;
};
