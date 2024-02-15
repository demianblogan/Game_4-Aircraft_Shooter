#include <iostream>

#include "Application.h"

int main()
{
	try
	{
		Application application;
		application.Run();
	}
	catch (const std::exception& exception)
	{
		std::cout << "EXCEPTION: " << exception.what() << '\n';
	}

    return 0;
}