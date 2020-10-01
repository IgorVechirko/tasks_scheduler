#ifndef TimeDelayTask_H
#define TimeDelayTask_H


#include "Task.h"


namespace TasksScheduler
{

	class TimeDelayTask : public Task
	{

		int _repeateAmount;





		virtual std::shared_ptr<Task> clone() override; 

		virtual void execute() override;

		virtual void showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime ) override;


	public:

		TimeDelayTask();
		virtual ~TimeDelayTask();

	};

}



#endif