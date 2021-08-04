#pragma once
class BaseField
{
public:
	BaseField() {};
	virtual std::ostream & print(std::ostream & os, bool flag,size_t index) const = 0;
	virtual std::string getAnswer()const { return m_answer; };
	virtual void changeField() = 0;
	virtual bool getCheckField(size_t index)const = 0;
	virtual ~BaseField() {};
protected:
	std::string m_question;
	std::string m_answer;
	std::string m_error_validator;
};