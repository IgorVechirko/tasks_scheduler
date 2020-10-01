#include "Application.h"
#include <iostream>


int main( int argc, char** argv )
{
	bool showIntro = argc < 2;

	int threadsAmount = 1;
	int fiboAmount = 5;
	int sortedAmount = 5;

	for( int i = 0; i < argc; i++ )
	{
		if ( i == 1 )
		{
			std::string str( argv[i] );
		
			if ( std::all_of(str.begin(), str.end(), ::isdigit) )
				threadsAmount = atoi( str.c_str() );
		}
		else if ( i == 2 )
		{
			std::string str( argv[i] );

			if ( std::all_of(str.begin(), str.end(), ::isdigit) )
				fiboAmount = atoi( str.c_str() );
		}
		else if ( i == 3 )
		{
			std::string str( argv[i] );
			
			if ( std::all_of(str.begin(), str.end(), ::isdigit) )
				sortedAmount = atoi( str.c_str() );
		}
	}

	if ( showIntro )
	{
		TasksScheduler::Console::log( "Your can configure program\n");
		TasksScheduler::Console::log( "Programm receive 3 arguments\n");
		TasksScheduler::Console::log( "1-st amount of active threads in scheduler ( default = 1 ) \n");
		TasksScheduler::Console::log( "2-nd amount of Fibonacci member calulation tasks ( default = 5 ) \n");
		TasksScheduler::Console::log( "3-rd amount of Sorting tasks ( default = 1 )\n\n");
		TasksScheduler::Console::log( "There will be add few simple repeatable tasks. They result will not display in output\n\n");
		TasksScheduler::Console::log( "Press Enter to continue\n\n");

		std::cin.get();
	}


	TasksScheduler::Application application(threadsAmount);
	application.run( fiboAmount, sortedAmount );

	std::cin.get();

	return 0;
}
