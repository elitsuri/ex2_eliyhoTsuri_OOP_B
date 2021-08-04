#pragma once
// A class that represents a form. A form has many fields
#include <vector>
#include "BaseField.h"
#include "BaseValidator.h"

class Form
{
public:
	Form() {};
	void addField(BaseField* field) { m_fields.push_back(field); };
	void addValidator(BaseValidator *validator) { m_vali.push_back(validator); }
	void fillForm();
	bool validateForm();
	std::ostream & getForm(std::ostream & os, bool &flag)const;
	std::ostream & getFields(std::ostream & os)const;
	~Form() {};
private:
	std::vector<BaseField *> m_fields;
	std::vector<BaseValidator *> m_vali;
};
std::ostream & operator<<(std::ostream & os, const Form& form);
