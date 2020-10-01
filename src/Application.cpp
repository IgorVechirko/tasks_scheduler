#include "Application.h"

#include "TimeDelayTask.h"
#include "SortBigArrayTask.h"
#include "CalcFibonacciNumTask.h"

namespace TasksScheduler
{

	Application::Application( int threadsAmount )
		: _tasksScheduler( threadsAmount )
	{
	}
	Application::~Application()
	{
	}
	void Application::generateTasks( int fiboTasksAmount, int sortTasksAmount )
	{
		_tasksScheduler.addTasks( std::make_shared<TimeDelayTask>(), 100, true );

		std::default_random_engine dre;
		std::uniform_int_distribution timeGen(10,10000);
		std::uniform_int_distribution arraySizeGen(1000000,10000000);
		std::uniform_int_distribution fiboNumGen(1000,2000);

	
		for( int i = 0; i < fiboTasksAmount; i++ )
			_tasksScheduler.addTasks( std::make_shared<CalcFibonacciNumTask>(fiboNumGen(dre)), timeGen(dre), false );


		for( int i = 0; i < sortTasksAmount; i++ )
			_tasksScheduler.addTasks( std::make_shared<SortBigArrayTask>(arraySizeGen(dre)), timeGen(dre), false );
		
	}
	void Application::run( int fiboTasksAmount, int sortTasksAmount )
	{
		generateTasks( fiboTasksAmount, sortTasksAmount );

		_lastUpdateTime = std::chrono::steady_clock::now();

		while( true )
		{
			auto currentTime = std::chrono::steady_clock::now();
			auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastUpdateTime);
			
			if ( deltaTime.count() > 0 )
			{
				_lastUpdateTime = currentTime;

				_tasksScheduler.update( static_cast<int>( deltaTime.count() ) );
			}
			else
			{
				std::this_thread::sleep_for( std::chrono::milliseconds(1) );
			}
		}
	}

}