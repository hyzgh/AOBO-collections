// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main ()
{
	if (std::regex_match ("subject1233", std::regex("(sub)(.?)(ject)(123)([3-3])") ))
		std::cout << "string literal matched\n";

	return 0;
}
