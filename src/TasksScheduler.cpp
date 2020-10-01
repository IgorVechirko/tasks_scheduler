#include "TasksScheduler.h"

#include "Task.h"

namespace TasksScheduler
{

	TasksScheduler::TasksScheduler( int threadsNumber )
		: _maxActiveTasksAmount( threadsNumber )
	{
		assert( _maxActiveTasksAmount );
	}
	TasksScheduler::~TasksScheduler()
	{
	}
	void TasksScheduler::increaseTimeAndFinishExecutingTasks( int deltaMs )
	{
		for( auto& taskInfo : _sortedExecutingTasksInfo )
		{
			taskInfo.timeInExecutingState += deltaMs;
			taskInfo.totalTimeInExecutingState += deltaMs;
			taskInfo.totalTimeInActiveState += deltaMs;
		}

		auto pastEndIt = std::remove_if( _sortedExecutingTasksInfo.begin(), _sortedExecutingTasksInfo.end(), [](const ExecutedTaskInfo& taskInfo){

			if ( taskInfo.task->getState() == Task::State::FNISHED )
			{
				taskInfo.task->showOutput( taskInfo.totalTimeInActiveState, taskInfo.totalTimeInExecutingState, taskInfo.taskActivatedTime );
			}

			return taskInfo.task->getState() == Task::State::FNISHED;
		} );
		_sortedExecutingTasksInfo.erase( pastEndIt, _sortedExecutingTasksInfo.end() );
	}
	void TasksScheduler::increaseSuspendedTasksTime( int deltaMs )
	{
		for( auto& taskInfo : _suspendedTasksInfo )
		{
			taskInfo.timeInSuspendState += deltaMs;
			taskInfo.totalTimeInActiveState += deltaMs;
		}
	}
	void TasksScheduler::updateAndActivateScheduledTasks( int deltaMs )
	{
		for( auto& taskInfo : _sortedScheduledTasksInfo )
			taskInfo.timeTillExecute -= deltaMs;

		while( !_sortedScheduledTasksInfo.empty() )
		{
			auto& scheduledTaskInfo = _sortedScheduledTasksInfo.front();
			if (scheduledTaskInfo.timeTillExecute > 0 )
				break;
			else
			{
				activateTask( scheduledTaskInfo.task );

				_sortedScheduledTasksInfo.pop_front();
			}
		}



		for( auto& taskInfo : _sortedRepeatableTasksInfo )
			taskInfo.timeTillExecute -= deltaMs;

		std::vector<RepeatableTaskInfo> completedRepeatableTasksInfo;

		auto checkingTasksIt = _sortedRepeatableTasksInfo.begin();
		while( checkingTasksIt != _sortedRepeatableTasksInfo.end() )
		{
			if ( checkingTasksIt->timeTillExecute <= 0 )
			{
				auto repeateAmount = abs(checkingTasksIt->timeTillExecute)/checkingTasksIt->repeateTime + 1;
				for( int i = 0; i < repeateAmount ; i++ )
					activateTask( checkingTasksIt->task->clone() );

				checkingTasksIt->timeTillExecute = checkingTasksIt->repeateTime;
				
				completedRepeatableTasksInfo.push_back( std::move(*checkingTasksIt) );

				checkingTasksIt = _sortedRepeatableTasksInfo.erase( checkingTasksIt );
			}
			else
			{
				break;
			}
		}

		for ( auto& checkingTaskInfo : completedRepeatableTasksInfo )
		{
			auto insertIt = _sortedRepeatableTasksInfo.begin();

			for( ; insertIt != _sortedRepeatableTasksInfo.end(); insertIt++ )
			{
				if ( insertIt->timeTillExecute > checkingTaskInfo.timeTillExecute )
					break;
			}

			_sortedRepeatableTasksInfo.insert( insertIt, std::move( checkingTaskInfo ) );
		}
	}
	void TasksScheduler::activateTask( std::shared_ptr<Task> task )
	{
		_suspendedTasksInfo.push_front(ExecutedTaskInfo());
		_suspendedTasksInfo.front().task = task;
		_suspendedTasksInfo.front().taskActivatedTime = _relativeTime;
	}
	void TasksScheduler::distributeThreadsBetweenActiveTasks()
	{
		_suspendedTasksInfo.insert( _suspendedTasksInfo.begin(), _sortedExecutingTasksInfo.begin(), _sortedExecutingTasksInfo.end() );
		_sortedExecutingTasksInfo.clear();

		std::list<ExecutedTaskInfo> sortedSuspendedTasks;

		while( !_suspendedTasksInfo.empty() )
		{
			auto& insertedTaskInfo = _suspendedTasksInfo.front();

			auto insertIt = sortedSuspendedTasks.begin();
			while( insertIt != sortedSuspendedTasks.end() )
			{
				if ( insertIt->totalTimeInExecutingState == 0 )
					insertIt++;
				else if ( insertedTaskInfo.totalTimeInExecutingState == 0 )
					break;
				else if ( insertIt->timeInSuspendState > 100 )
					insertIt++;
				else if ( insertedTaskInfo.timeInSuspendState > 100 )
					break;
				else if ( insertIt->timeInSuspendState > insertedTaskInfo.timeInSuspendState ) 
					insertIt++;
				else
					break;
			}

			sortedSuspendedTasks.insert( insertIt, std::move( _suspendedTasksInfo.front() ) );
			_suspendedTasksInfo.pop_front();
		}

		std::swap( sortedSuspendedTasks, _suspendedTasksInfo );

		auto freeTasksAmount = _maxActiveTasksAmount - _sortedExecutingTasksInfo.size();

		for( int i = 0; i < freeTasksAmount && !_suspendedTasksInfo.empty(); i++ )
		{
			auto& newExecutinTask = _suspendedTasksInfo.front();
			newExecutinTask.timeInExecutingState = 0;
			newExecutinTask.timeInSuspendState = 0;
			newExecutinTask.task->resume();

			_sortedExecutingTasksInfo.push_back( std::move( newExecutinTask ) );
			_suspendedTasksInfo.pop_front();
		}

		for( auto& executingTaskInfo : _sortedExecutingTasksInfo )
			executingTaskInfo.task->resume();

		for( auto& suspendedTaskInfo : _suspendedTasksInfo )
			suspendedTaskInfo.task->resume();

	}
	void TasksScheduler::addTasks( std::shared_ptr<Task> task, int delayMs, bool repeateable )
	{
		if( repeateable )
		{
			if ( delayMs > 0 )
			{
				auto insertIt = _sortedRepeatableTasksInfo.begin();

				for( ; insertIt != _sortedRepeatableTasksInfo.end(); insertIt++ )
				{
					if ( insertIt->timeTillExecute > delayMs )
						break;
				}

				auto newTaskIt = _sortedRepeatableTasksInfo.insert( insertIt, RepeatableTaskInfo() );

				newTaskIt->timeTillExecute = delayMs;
				newTaskIt->repeateTime = delayMs;
				newTaskIt->task = task;
			}
		}
		else
		{
			auto insertIt = _sortedScheduledTasksInfo.begin();

			for( ; insertIt != _sortedScheduledTasksInfo.end(); insertIt++ )
			{
				if ( insertIt->timeTillExecute > delayMs )
					break;
			}

			auto newTaskIt = _sortedScheduledTasksInfo.insert( insertIt, ScheduledTaskInfo() );

			newTaskIt->task = task;
			newTaskIt->timeTillExecute = delayMs;
		}
	}
	void TasksScheduler::update( int deltaMs  )
	{
		_relativeTime += deltaMs; 

		increaseTimeAndFinishExecutingTasks( deltaMs );
		increaseSuspendedTasksTime( deltaMs );

		updateAndActivateScheduledTasks( deltaMs );

		distributeThreadsBetweenActiveTasks();

		if ( false && ( !_sortedExecutingTasksInfo.empty() || !_suspendedTasksInfo.empty() ) )
		{
			std::string outputStr = "ms = " ;
			outputStr += std::to_string( deltaMs );
			outputStr += ", executing tasks = ";
			outputStr += std::to_string( _sortedExecutingTasksInfo.size() );
			outputStr += ", suspended tasks = ";
			outputStr += std::to_string( _suspendedTasksInfo.size() );
			outputStr += "\n";
			Console::log( outputStr );
		}
	}
}