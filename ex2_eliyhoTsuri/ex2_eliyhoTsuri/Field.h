#pragma once
// A class that represents a field. A field can have one or more validator
#include <iostream>
#include <memory>
#include <cctype>
#include <vector>
#include <cstdlib> // for system()

#include "BaseField.h"
#include "BaseValidator.h"
#include "RangeValidator.h"
using::std::string;
template <typename T>
class Field : public BaseField
{
public:
	Field(string field);
	void addValidator(Validator<T> *validator) { m_vecVali.push_back(validator); };
	virtual std::ostream &print(std::ostream & os, bool flag, size_t index) const;
	virtual bool getCheckField(size_t index)const;
	void changeField();
	T getVar()const { return m_Var; };
	~Field() {};
protected:
	T m_Var;
	std::vector<Validator<T>* > m_vecVali;
};

template<typename Item>
Field<Item>::Field(string field)
{
	m_question = field;
	std::cout << m_question <<"\n";
	std::cin >> m_answer;
}

template<typename T>
std::ostream & Field<T>::print(std::ostream & os,bool flag,size_t index) const
{
	string str = m_question;
	string temp = m_answer;
	if (temp == "1")
		temp = "Computer Science";
	else if (temp == "2")
		temp = "Literature";
	else if (temp == "3")
		temp = "Medicine";
	std::cout << "\n+==========================================================+\n";

	str.append(string(" = ").append(string(temp).append(string("\n"))));
	os << str;
	if (!flag)
	{
		for (size_t i = 0; i < m_vecVali.size(); i++)
		{
			if (i == index)
				m_vecVali[i]->print(os);
		}
	}
	return os;
}

template<typename T>
bool Field<T>::getCheckField(size_t index)const
{
	if (index == 0)
	{
		NoDigitValidator name(this->m_answer);
		if (!name.getCheckValidator())
			return false;
	}
	else if (index == 1)
	{
		IDValidator id(this->m_answer);
		if (!id.getCheckValidator())
			return false;
	}
	else if (index == 2)
	{
		RangeValidator<int> yearBirth(this->m_answer);
		if (!yearBirth.getCheck())
			return false;
	}
	else if (index == 3)
	{
		FacultyValue faculty(this->m_answer);
		if (!faculty.getCheckValidator())
			return false;
	}
	else if (index == 4)
	{
		RangeValidator<int> studYear(this->m_answer);
		if (!studYear.getCheck())
			return false;
	}
	else if (index == 5)
	{
		MinValidator<int> minCourse(this->m_answer);
		if (!minCourse.getCheckValidator())
			return false;
	}
	return true;
}
template<typename T>
void Field<T>::changeField()
{
	std::cout << m_question << " = ";
	std::cout << m_answer << "\n";
	std::cout << m_vecVali[0]->getError() << "\n";
	std::cout << "Enter new answer \n";
	std::cin >> m_answer;
}
