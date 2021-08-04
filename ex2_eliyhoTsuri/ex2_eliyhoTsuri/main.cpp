#include <memory>
#include <string>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <cstdlib> // for system()
#include <vector>
#include "Field.h"
#include "Form.h"
#include "FacultyValue.h"
#include "NoDigitValidator.h"
#include "IDValidator.h"
#include "RangeValidator.h"
#include "MinValidator.h"
#include "Faculty2YearValidator.h"
#include "Courses2YearValidator.h"
// ---------------- Function declarations ------------------
void displayWelcomeMessage(std::ostream& ostr);
void displayGoodbyeMessage(std::ostream& ostr);
void displayErrorMessage(std::ostream& ostr);
void displayFormFields(std::ostream& ostr, const Form& form);
void clearScreen();
int currentYear();
// ----------------------- consts --------------------------
const int MAX_POSSIBLE_YEAR = 7;
const int MIN_AGE = 16;
const int MAX_AGE = 100;
// ------------------------ main ---------------------------
int main()
{
	// Creating the form fields
	auto nameField = std::make_unique<Field<std::string>>("What is your name?");
	auto idField = std::make_unique<Field<uint32_t>>("What is you ID?");
	auto yearOfBirthField = std::make_unique<Field<int>>("What is your year of birth?");
	auto facultyField = std::make_unique<Field<FacultyValue>>("What faculty you are registering to?\n"
															  "(1-Computer Science, 2-Medicine, 3-Literature)");
	auto yearField = std::make_unique<Field<int>>("Which year is it in your studies? (1-"
												  + std::to_string(MAX_POSSIBLE_YEAR) + ")");
	auto courseField = std::make_unique<Field<short>>("How many courses you are taking this year?");

	// Creating the field validators
	auto nameValidator = std::make_unique <NoDigitValidator>();
	auto idValidator = std::make_unique <IDValidator>();
	auto ageValidator = std::make_unique <RangeValidator<int>>(currentYear() - MAX_AGE, currentYear() - MIN_AGE);
	auto facultyValidator = std::make_unique <RangeValidator<FacultyValue>>(1, 3);
	auto yearValidator = std::make_unique <RangeValidator<int>>(1, MAX_POSSIBLE_YEAR);
	auto courseValidator = std::make_unique <MinValidator<short>>(2);

	// Adding the validators to the fields
	nameField->addValidator(nameValidator.get());
	idField->addValidator(idValidator.get());
	yearOfBirthField->addValidator(ageValidator.get());
	facultyField->addValidator(facultyValidator.get());
	yearField->addValidator(yearValidator.get());
	courseField->addValidator(courseValidator.get());

	// Creating form validators
	auto facultyToYearValidator
		= std::make_unique<Faculty2YearValidator<Field<FacultyValue>, Field<int>>>(facultyField.get(), yearField.get());
	auto coursesToYearValidator
		= std::make_unique<Courses2YearValidator<Field<short>, Field<int>>>(courseField.get(), yearField.get());
	// Creating the form and adding the fields to it
	Form myForm;
	myForm.addField(nameField.get());
	myForm.addField(idField.get());
	myForm.addField(yearOfBirthField.get());
	myForm.addField(facultyField.get());
	myForm.addField(yearField.get());
	myForm.addField(courseField.get());
	// Adding form validators
	myForm.addValidator(facultyToYearValidator.get());
	myForm.addValidator(coursesToYearValidator.get());
	// Getting the information from the user
	clearScreen();
	displayWelcomeMessage(std::cout);
	// Get the input only for empty or not valid fields
	myForm.fillForm();

	// Validation loop
	for (auto formIsCorrect = myForm.validateForm(); 
		 ! formIsCorrect; formIsCorrect = myForm.validateForm())
	{
		// Displays all form fields with value (and error if not valid)
		clearScreen();
		displayErrorMessage(std::cout);
		displayFormFields(std::cout, myForm);
		myForm.fillForm();
	}
	clearScreen();
	displayGoodbyeMessage(std::cout);
	displayFormFields(std::cout, myForm);
}
// ---------------------------------------------------------
void displayFormFields(std::ostream& ostr, const Form& form)
{
	ostr << form << '\n';
}
// ---------------------------------------------------------
void displayWelcomeMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|                  Hello and welcome!                      |\n"
		"|  In order to register please fill in the fields below    |\n"
		"+----------------------------------------------------------+\n";
}
// ---------------------------------------------------------
void displayErrorMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|     There was an error in at least one of the fields!    |\n"
		"|                Please correct the error(s)               |\n"
		"+----------------------------------------------------------+\n";
}
// ---------------------------------------------------------
void displayGoodbyeMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|                      Thank you!                          |\n"
		"|               This is the data you sent:                 |\n"
		"+----------------------------------------------------------+\n";
}
// ---------------------------------------------------------
void clearScreen()
{
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
}
// ---------------------------------------------------------
std::tm localtime(const time_t& time)
{
#ifdef _MSC_VER
	std::tm calendarTime = {};
	localtime_s(&calendarTime, &time);
	return calendarTime;
#else
	return *std::localtime(&time);
#endif
}
// ---------------------------------------------------------
int currentYear()
{
	using clock = std::chrono::system_clock;
	auto now = clock::to_time_t(clock::now());
	return localtime(now).tm_year + 1900;
}