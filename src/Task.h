#ifndef Task_H
#define Task_H


#include "Common.h"
#include <Windows.h>


namespace TasksScheduler
{
	class Task
	{

	public:

		enum class State
		{
			NONE,
			EXECUTING,
			SUSPENDED,
			FNISHED
		};


	private:

		friend DWORD WINAPI threadFunction( LPVOID lpParam );

		State _state;
		std::recursive_mutex _stateLock;


		HANDLE _threadHandle;
		DWORD _threadID;


		void onThreadFinish();
	
	public:

		Task();
		virtual ~Task();

		virtual std::shared_ptr<Task> clone() = 0; 

		virtual void execute() = 0;

		virtual void showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime ) = 0;

		void activate();
		void suspend();
		void resume();

		State getState();

	};

}


#endif