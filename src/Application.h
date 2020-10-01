#ifndef Application_H
#define Application_H

#include "TasksScheduler.h"
#include <chrono>

namespace TasksScheduler
{

	class Application
	{

		std::chrono::steady_clock::time_point _lastUpdateTime;

		TasksScheduler _tasksScheduler;



		void generateTasks( int fiboTasksAmount, int sortTasksAmount );


	public:

		Application( int threadsAmount );
		virtual ~Application();

		void run( int fiboTasksAmount, int sortTasksAmount );
	};

}




#endif