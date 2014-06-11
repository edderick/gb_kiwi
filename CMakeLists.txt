cmake_minimum_required(VERSION 2.6)
project(GB_Kiwi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GB_Kiwi_SOURCE_DIR}/cmake")
set(BIN_DIR ${GB_Kiwi_SOURCE_DIR}/bin)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(GB_Kiwi 
    cpu.cpp 
    Memory.cpp 
    Bootstrap.cpp 
    Cart.cpp 
    Graphics.cpp)

target_link_libraries(GB_Kiwi ${SDL2_LIBRARY})
install(TARGETS GB_Kiwi RUNTIME DESTINATION ${BIN_DIR})
