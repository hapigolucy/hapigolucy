cmake_minimum_required(VERSION 3.0)

project(Miscellaneous)

#Build Type: Debug / Release
IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
ELSE()
  set(CMAKE_BUILD_TYPE "Release")
  message("Default build type : Release.")
ENDIF()

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")


#Library Support
set(USE_LIBRARY ${USE_LIBRARY})
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")
set(BUILD_SHARED_LIBS OFF)


add_definitions(-g -std=c++14)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

# include
include_directories( ./include )

set(main
	main.cpp)

set(sources
	./src/Algorithms.cpp
	./src/Async.cpp
	./src/ConditionVariable.cpp
	./src/Graph.cpp
	./src/MoveMyData.cpp
	./src/OpenClosedPrinciple.cpp
	./src/Student.cpp
	./src/ThreadSafeQueue.cpp
	./src/AssociativeContainer.cpp
	./src/BinarySearchTree.cpp
	./src/Graph2.cpp
	./src/MathFuncs.cpp
	./src/MoveSemantics.cpp
	./src/StringsRegEx.cpp
	./src/TemplateGrid.cpp
	./src/ThreadWrapper.cpp)

if(USE_LIBRARY)
	# add_library will create a static library
	# since BUILD_SHARED_LIBS is OFF
	add_library(Source ${sources})
	add_executable(Misc ${main})
	target_link_libraries(Misc Source pthread)
else()
	add_executable(Misc ${main} ${sources})
	target_link_libraries(Misc pthread)
endif()
