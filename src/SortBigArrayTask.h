#ifndef SortBigArrayTask_H
#define SortBigArrayTask_H


#include "Task.h"


namespace TasksScheduler
{

	class SortBigArrayTask : public Task
	{
		
		std::vector<int> _sortedVec;


		virtual std::shared_ptr<Task> clone() override; 

		virtual void execute() override;

		virtual void showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime ) override;

	public:

		SortBigArrayTask( int elemInArray = 1 );
		virtual ~SortBigArrayTask();

	};

}



#endif