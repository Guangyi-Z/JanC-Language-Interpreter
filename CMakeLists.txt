cmake_minimum_required(VERSION 2.8)
project(scheme CXX)

###########################
# Settings related to g++ #
###########################
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -I /usr/include/mysql -m64  -O3 -DOS_LINUX  -lmysqlclient -lmysqlcppconn -lpthread -L /usr/lib64/mysql ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(LIB_ROOT ./lib)

############################
# Setting for dependencies #
############################

################
# Intergration #
################
add_subdirectory(src)
add_executable(run src/main.cpp)
# include_directories(./src)
# target_link_libraries(run)

####################
# Setup googletest #
####################
add_subdirectory(lib/gtest-1.7.0)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) 
enable_testing()

# function that create test cases.
function(add_gtest item)
  target_link_libraries(${item} gtest_main)
  add_test(${item} ${item})
endfunction()

##############
# Test cases #
##############
# Options related to test cases.
# option(test_example "an example." ON)
add_subdirectory(test/test_example)
