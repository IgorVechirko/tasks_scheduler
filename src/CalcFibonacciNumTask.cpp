#include "CalcFibonacciNumTask.h"


namespace TasksScheduler
{

	CalcFibonacciNumTask::CalcFibonacciNumTask()
		: _elemNumForCalc( 0 )
		, _elemValue( 0 )
	{
	}
	CalcFibonacciNumTask::CalcFibonacciNumTask( int elemNum )
		: _elemNumForCalc( elemNum )
	{
	}
	CalcFibonacciNumTask::~CalcFibonacciNumTask()
	{
	}
	std::shared_ptr<Task> CalcFibonacciNumTask::clone()
	{
		auto result = std::make_shared<CalcFibonacciNumTask>();

		if ( result )
			result->_elemNumForCalc = _elemNumForCalc;

		return result;
	}
	int CalcFibonacciNumTask::getFibonacciElem( int elemNum )
	{
		if ( elemNum < 0 )
			return 0;
		if ( elemNum == 0 )
			return 1;
		else
			return getFibonacciElem( elemNum - 1) + elemNum;
	}
	void CalcFibonacciNumTask::execute()
	{
		_elemValue = getFibonacciElem( _elemNumForCalc );
	}
	void CalcFibonacciNumTask::showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime )
	{		
		std::string outputStr = "Fibonacci task finish\n";
		outputStr += std::string( "activate time = " ) + std::to_string(taskActivateTime) + std::string("\n");
		outputStr += std::string( "time in active state = " ) += std::to_string( taskTimeInActiveState) += std::string("\n");
		outputStr += std::string("time in execution staet = " ) += std::to_string( taskTimeInExecutionState) += std::string("\n");
		outputStr += std::to_string( _elemNumForCalc ) + std::string( " Fibonacci elem  = " ) + std::to_string( _elemValue ) + std::string("\n") + std::string("\n");

		Console::log( outputStr );
	}
}