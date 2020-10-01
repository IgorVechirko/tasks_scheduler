#ifndef Common_H
#define Common_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <deque>
#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <mutex>
#include <random>
#include <chrono>
#include <atomic>
#include <assert.h>


#define MAKE_UNCOPYABLE(__TYPE__)\
__TYPE__( const __TYPE__& ) = delete;\
__TYPE__( __TYPE__&& ) = delete;\
const __TYPE__& operator= ( const __TYPE__& ) = delete;\
const __TYPE__& operator= ( __TYPE__&& ) = delete;\


namespace TasksScheduler
{
	class Console
	{
		static std::recursive_mutex _outputLocker;

	public:
	
		static void log()
		{
			
			//std::cout << std::endl;
		}
		template<typename FirstType, typename... Types>
		static void log( const FirstType& firstArg, const Types&... otherArgs )
		{
			std::scoped_lock lock(_outputLocker);
			std::cout << firstArg;
			log( otherArgs... );
		}
	};
}



#endif