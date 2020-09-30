//#include "Application.h"
#include <iostream>


int main( int argc, char** argv )
{
	//BulletsMng::Application application;
	//application.run();


	for( int i = 0; i < argc; i++ )
		std::cout << argv[i] << std::endl;

	std::cin.get();


	return 0;
}
