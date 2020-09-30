CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )

project( tasks_scheduler VERSION 0.1.0.0 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( TASKS_SCHEDULER_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( TASKS_SCHEDULER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )



set( entry_point ${TASKS_SCHEDULER_SRC_DIR}/main.cpp )

set( TASKS_SCHEDULER_SRC 
                    ${entry_point}
)

add_executable( tasks_scheduler ${TASKS_SCHEDULER_SRC} )

if ( MSVC )
    target_compile_options( tasks_scheduler PRIVATE /MP )

	target_compile_options( tasks_scheduler PRIVATE /wd4018)

endif()