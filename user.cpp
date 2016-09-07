#include <string>
#include "user.h"

User::User(std::string ValueName, std::string ValueMail, int ValueLevel, int ValueSubmit, int ValueCorrect, std::string ValuePassword):name(ValueName), mail(ValueMail), level(ValueLevel), submit(ValueSubmit), correct(ValueCorrect), password(ValuePassword){}
std::string User::GetName()
{
	return name;
}

void User::SetName(std::string ValueName)
{
	name = ValueName;
}
	
std::string User::GetMail()
{
	return mail;
}

void User::SetMail(std::string ValueMail)
{
	mail = ValueMail;
}

int User::GetLevel()
{
	return level;
}

void User::SetLevel(int ValueLevel)
{
	level = ValueLevel;
}

int User::GetSubmit()
{
	return submit;
}

void User::SetSubmit(int ValueSubmit)
{
	submit = ValueSubmit;
}

int User::GetCorrect()
{
	return correct;
}

void User::SetCorrect(int ValueCorrect)
{
	correct = ValueCorrect;
}

std::string User::GetPassword()
{
	return password;
}

void User::SetPassword(std::string ValuePassword)
{
	password = ValuePassword;
}

