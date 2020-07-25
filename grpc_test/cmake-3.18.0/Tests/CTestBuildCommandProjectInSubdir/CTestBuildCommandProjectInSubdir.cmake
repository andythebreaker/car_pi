cmake_minimum_required(VERSION 2.8.10)

set(CTEST_SOURCE_DIRECTORY "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/VSProjectInSubdir")
set(CTEST_BINARY_DIRECTORY "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CTestBuildCommandProjectInSubdir/Nested")
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_BUILD_CONFIGURATION "Release")

ctest_empty_binary_directory(${CTEST_BINARY_DIRECTORY})
ctest_start(Experimental)
ctest_configure(OPTIONS "-DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make")
ctest_build(TARGET test)
