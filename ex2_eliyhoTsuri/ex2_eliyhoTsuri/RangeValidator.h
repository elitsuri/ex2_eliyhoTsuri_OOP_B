#pragma once
// A class that represents a range validator.
// It validates if a field value is in some range.
// The type used as template parameter must implement < and > operators.
#include "NumbersValidator.h"
template <class T>
class RangeValidator :public NumbersValidator<T>
{
public:
	RangeValidator(std::string field)
	{
		
		if (field.size() == 1)
		{
			char year[1];
			year[0] = field[0];
			m_year = atoi(year);
			if (1 <= m_year && m_year <= 7)
				m_check_validator = true;
			else
				m_check_validator = false;
		}
		else
		{
			m_range1 = 1918;
			m_range2 = 2002;
			char year[9];
			unsigned index = 0;
			while (index < field.size())
			{
				year[index] = field[index];
				index++;
			}
			m_year = atoi(year);
			if (1918 <= m_year && m_year <= 2002)
				m_check_validator = true;
			else
				m_check_validator = false;
		}
	};
	RangeValidator(int range1, int range2) :m_range1(range1), m_range2(range2) {};
	virtual bool checkField(const T &field)const override
	{
		return m_check_validator;
	}
	bool getCheck() { return m_check_validator; };
	~RangeValidator() {};
private:
	int m_range1;
	int m_range2;
	int m_year;
	bool m_check_validator;
};