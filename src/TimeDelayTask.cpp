#include "TimeDelayTask.h"


namespace TasksScheduler
{


	TimeDelayTask::TimeDelayTask()
		: _repeateAmount( 2 )
	{
	}
	TimeDelayTask::~TimeDelayTask()
	{
	}
	std::shared_ptr<Task> TimeDelayTask::clone()
	{
		auto result = std::make_shared<TimeDelayTask>();

		if ( result )
			result->_repeateAmount = _repeateAmount;

		return result;
	}
	void TimeDelayTask::showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime )
	{

	}
	void TimeDelayTask::execute()
	{
		std::default_random_engine dre;
		std::uniform_int_distribution randGen( 10, 20 );

		while( _repeateAmount > 0 )
		{
			_repeateAmount--;
			std::this_thread::sleep_for( std::chrono::microseconds( randGen(dre) ) );
		}
	}

}