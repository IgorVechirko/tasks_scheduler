#ifndef CalcFibonacciNumTask_H
#define CalcFibonacciNumTask_H


#include "Task.h"


namespace TasksScheduler
{

	class CalcFibonacciNumTask : public Task
	{

		int _elemNumForCalc;
		int _elemValue;



		virtual std::shared_ptr<Task> clone() override; 

		virtual void execute() override;

		virtual void showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime ) override;

		int getFibonacciElem( int elemNum );

	public:

		CalcFibonacciNumTask();
		CalcFibonacciNumTask( int elemNum );
		virtual ~CalcFibonacciNumTask();

	};

}



#endif