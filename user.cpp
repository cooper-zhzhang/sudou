#include <string>
#include "user.h"

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

int User::GetRight()
{
	return right;
}

void User::SetRight(int ValueRight)
{
	right = ValueRight;
}

std::string User::GetPassword()
{
	return password;
}

void User::SetPassword(std::string ValuePassword)
{
	password = ValuePassword;
}

