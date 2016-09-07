#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User() = default;

	//User()
	std::string GetName();

	void SetName(std::string ValueName);
	
	std::string GetMail();

	void SetMail(std::string ValueMail);

	int GetLevel();

	void SetLevel(int ValueLevel);

	int GetSubmit();

	void SetSubmit(int ValueSubmit);

	int GetRight();

	void SetRight(int ValueRight);

	std::string GetPassword();

	void SetPassword(std::string ValuePassword);

private:
	std::string name;
	std::string mail;
	int level;
	int submit;
	int right;
	std::string password;
};

#endif //USER_H
