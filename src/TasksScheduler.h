#ifndef TasksScheduler_H
#define TasksScheduler_H

#include "Common.h"

namespace TasksScheduler
{
	
	class Task;
	class TasksScheduler
	{
		struct ScheduledTaskInfo
		{
			int timeTillExecute;

			std::shared_ptr<Task> task;

			ScheduledTaskInfo()
				: timeTillExecute( 0 )
			{}
		};

		struct RepeatableTaskInfo : public ScheduledTaskInfo
		{
			int repeateTime;

			RepeatableTaskInfo()
				: repeateTime( 0 )
			{}
		};

		struct ExecutedTaskInfo
		{
			std::shared_ptr<Task> task;

			int totalTimeInActiveState;
			int totalTimeInExecutingState;

			int timeInExecutingState;
			int timeInSuspendState;

			int taskActivatedTime;

			ExecutedTaskInfo()
				: timeInExecutingState( 0 )
				, timeInSuspendState( 0 )
				, totalTimeInExecutingState( 0 )
				, totalTimeInActiveState( 0 )
				, taskActivatedTime( 0 )
			{}
		};


		std::list<ScheduledTaskInfo> _sortedScheduledTasksInfo;
		std::list<RepeatableTaskInfo> _sortedRepeatableTasksInfo;

		std::list<ExecutedTaskInfo> _sortedExecutingTasksInfo;
		std::list<ExecutedTaskInfo> _suspendedTasksInfo;

		int _relativeTime;

		int _maxActiveTasksAmount;



		void increaseTimeAndFinishExecutingTasks( int deltaMs );
		void increaseSuspendedTasksTime( int deltaMs );
		
		void updateAndActivateScheduledTasks( int deltaMs );
		
		void activateTask( std::shared_ptr<Task> task );
		
		void distributeThreadsBetweenActiveTasks();

		public:

			TasksScheduler( int threadsNumber = 1 );
			virtual ~TasksScheduler();

			void addTasks( std::shared_ptr<Task> task, int delayMs = 0, bool repeateable = false );

			void update( int deltaMs );

	};



}



#endif