#include "Form.h"
#include <iostream>
void Form::fillForm()
{
	for (size_t i = 0; i < m_fields.size(); ++i)
	{
		if (!m_fields[i]->getCheckField(i))
			m_fields[i]->changeField();	
	}
}
bool Form::validateForm()
{
	for (size_t i = 0; i < m_fields.size(); ++i)
	{
		if (!m_fields[i]->getCheckField(i))
			return false;
	}
	return true;
}



std::ostream & Form::getForm(std::ostream & os, bool &flag)const
{
	return os;
}

std::ostream & Form::getFields(std::ostream & os)const
{
	for (size_t i = 0; i < m_fields.size(); i++)
		m_fields[i]->print(os, true, i);
	return os;
}



std::ostream & operator<<(std::ostream & os, const Form& form)
{
	bool flag;
	form.getForm(os, flag);
	form.getFields(os);
	return os;
}
