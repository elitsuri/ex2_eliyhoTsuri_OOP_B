#pragma once
// A class that represents an ID validator.
// ID validation is done using the control digit.
// Works only on the type 'uint32_t'.
#include "PersonValidator.h"
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string>
class IDValidator : public PersonValidator<uint32_t>
{
public:
	IDValidator(std::string id) 
	{
		m_error_validator = "Wrong control digit\n";

		char id_num[9];
		unsigned index = 0;

		while (index < id.size())
		{
			id_num[index] = id[index];
			index++;
		}
		m_id = atoi(id_num);
		m_check_validator = checkField(m_id);
	};
	IDValidator()
	{
		m_error_validator = "Wrong control digit";
		m_check_validator = false;
	}
	virtual bool checkField(const uint32_t & check_id)const override
	{
		if (check_id >= std::pow(10, 9))
			return false;
		std::uint32_t answer = check_id;
		int ins = answer % 10;
		answer /= 10;
		int t1, t2;
		int sum = 0, counter = 1;
		while (answer != 0)
		{
			t1 = answer % 10;
			answer /= 10;
			if (counter % 2 != 0)
				t1 *= 2;
			counter++;
			if (t1 > 9)
			{
				t2 = t1 % 10;
				t1 /= 10;
				t1 += t2;
			}
			sum += t1;
		}
		if ((ins + sum) % 10 == 0)
			return true;
		return false;
	}
	~IDValidator() {};
private:
	uint32_t m_id;
};