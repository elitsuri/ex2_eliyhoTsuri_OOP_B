#pragma once
// A class that represents a faculty-vs.-year validator.
// It checks if the faculty and year supplied matches each other.
// The types used as template parameter must be Field.
#include "StudyValidator.h"
template <typename T, class T1>
class Faculty2YearValidator :public StudyValidator<T>
{
public:
	Faculty2YearValidator(T *faculty, T1 *range)
		:m_course(faculty), m_year(range) {};
	virtual bool checkField(const T &field)const override
	{
		return false;
	}
	~Faculty2YearValidator() {};
private:
	T *m_course;
	T1 *m_year;
};
