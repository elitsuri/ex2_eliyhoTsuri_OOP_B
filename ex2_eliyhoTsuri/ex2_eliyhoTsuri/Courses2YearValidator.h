#pragma once
// A class that represents a courses-vs.-year validator.
// It checks if the course count and year supplied matches each other.
// The types used as template parameter must be Field.
#include "StudyValidator.h"
template <class T, class T1>
class Courses2YearValidator :public StudyValidator<T>
{
public:
	Courses2YearValidator(T *year, T1 *course) :m_course(course), m_year(year) {};
	virtual bool checkField(const T &field)const override
	{
		return false;
	}
	~Courses2YearValidator() {};
private:
	T1 *m_course;
	T *m_year;
};
