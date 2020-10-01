#include "Task.h"

namespace TasksScheduler
{
	DWORD WINAPI threadFunction( LPVOID lpParam )
	{
		auto tast = static_cast<Task*>(lpParam);
		
		tast->execute();
		tast->onThreadFinish();

		return 0;
	}

	Task::Task()
		: _state( State::NONE )
		, _threadID(NULL)
		, _threadHandle(NULL)
	{
	}
	Task::~Task()
	{
		if ( _threadHandle != NULL )
			CloseHandle( _threadHandle );
	}
	void Task::onThreadFinish()
	{
		std::scoped_lock locker(_stateLock);
		_state = State::FNISHED;
	}
	void Task::activate()
	{
		std::scoped_lock locker(_stateLock);

		if ( _state == State::NONE )
		{
			_threadHandle = CreateThread(
				NULL,
				0,
				threadFunction,
				(LPVOID)this,
				0,
				&_threadID );

			if( _threadHandle == NULL )
			{
				_state = State::FNISHED;
			}
			else
				_state = State::EXECUTING;
		}
	}
	void Task::suspend()
	{
		std::scoped_lock locker(_stateLock);

		if ( _state == State::EXECUTING )
		{
			SuspendThread( _threadHandle );
			_state = State::SUSPENDED;
		}
	}
	void Task::resume()
	{
		std::scoped_lock locker(_stateLock);

		if ( _state == State::SUSPENDED )
		{
			ResumeThread( _threadHandle );
			_state = State::EXECUTING;
		}
		else if ( _state == State::NONE )
			activate();
	}
	Task::State Task::getState()
	{
		std::scoped_lock locker(_stateLock);
		auto result = _state;

		return result;
	}
}