#include "SortBigArrayTask.h"


namespace TasksScheduler
{


	SortBigArrayTask::SortBigArrayTask( int elemInArray )
	{
		std::default_random_engine dre;
		std::uniform_int_distribution<int> di(10,1000);

		_sortedVec.resize(elemInArray);
		for( auto& vecElem : _sortedVec )
			vecElem = di(dre);
	}
	SortBigArrayTask::~SortBigArrayTask()
	{
	}
	std::shared_ptr<Task> SortBigArrayTask::clone()
	{
		auto result = std::make_shared<SortBigArrayTask>();

		if ( result )
			result->_sortedVec = _sortedVec;

		return result;
	}
	void SortBigArrayTask::execute()
	{
		std::sort( _sortedVec.begin(), _sortedVec.end() );
	}
	void SortBigArrayTask::showOutput( int taskTimeInActiveState, int taskTimeInExecutionState, int taskActivateTime )
	{
		std::string outputStr = "Sorted task finish\n";
		outputStr += std::string( "activate time = " ) + std::to_string(taskActivateTime) + std::string("\n");
		outputStr += std::string( "time in active state = " ) += std::to_string( taskTimeInActiveState) += std::string("\n");
		outputStr += std::string("time in execution staet = " ) += std::to_string( taskTimeInExecutionState) += std::string("\n");
		outputStr += std::string("first elem = ") + std::to_string( _sortedVec.front() ) + std::string(", last elem = ") + std::to_string( _sortedVec.back() ) + std::string("\n") + std::string("\n");

		Console::log( outputStr );
	}

}