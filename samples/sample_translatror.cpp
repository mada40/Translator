#include <iostream>
#include "translator.h"
#include <string>
int main()
{
	while (true)
	{
		std::cout << "Enter an expression, separating each token with a space:\n";
		std::string str;
		std::getline(std::cin, str);
		Translator tr(str);
		try
		{
			if (tr.have_vars()) tr.read_vars();
			double res = tr.solve();
			std::cout << str << " = " << res << "\n";
		}
		catch (const std::exception&)
		{
			std::cout << "\nWRONG, TRY AGAIN\n" << std::endl;
		}

		std::cout << "Continue execution? (n - NO / any other symbol - YES): ";
		char ans; std::cin >> ans;
		if (ans == 'n' || ans == 'N') break;

		std::cin.ignore();
	}

	return 0;
}
