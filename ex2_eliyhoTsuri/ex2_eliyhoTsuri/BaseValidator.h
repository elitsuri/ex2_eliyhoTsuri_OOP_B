#pragma once
#include <string>
class BaseValidator
{
public:
	BaseValidator() {};
	~BaseValidator() {};
	virtual bool getCheckValidator() = 0;
	std::ostream & print(std::ostream & os) const { os << m_error_validator; return os; }
	std::string & getError() { return m_error_validator; }

protected:
	bool m_check_validator = false;
	std::string m_error_validator = "Out of range";
};