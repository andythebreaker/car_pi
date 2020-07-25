# create the binary directory
make_directory("/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly")

# remove the CMakeCache.txt file from the source dir
# if there is one, so that in-source cmake tests
# still pass
message("Remove: /home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/COnly/CMakeCache.txt")
file(REMOVE "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/COnly/CMakeCache.txt")

# run cmake in the binary directory
message("running: ${CMAKE_COMMAND}")
execute_process(COMMAND "${CMAKE_COMMAND}"
  "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/COnly"
  "-GUnix Makefiles"
  -A ""
  -T ""
  WORKING_DIRECTORY "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly"
  RESULT_VARIABLE RESULT)
if(RESULT)
  message(FATAL_ERROR "Error running cmake command")
endif()

# Now use the --build option to build the project
message("running: ${CMAKE_COMMAND} --build")
execute_process(COMMAND "${CMAKE_COMMAND}"
  --build "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly" --config Debug
  RESULT_VARIABLE RESULT)
if(RESULT)
  message(FATAL_ERROR "Error running cmake --build")
endif()

# run the executable out of the Debug directory if using a
# multi-config generator
set(_isMultiConfig 0)
if(_isMultiConfig)
  set(RUN_TEST "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly/Debug/COnly")
else()
  set(RUN_TEST "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly/COnly")
endif()
# run the test results
message("running [${RUN_TEST}]")
execute_process(COMMAND "${RUN_TEST}" RESULT_VARIABLE RESULT)
if(RESULT)
  message(FATAL_ERROR "Error running test COnly")
endif()

# build it again with clean and only COnly target
execute_process(COMMAND "${CMAKE_COMMAND}"
  --build "/home/wp2018/user/andythebreaker/car_pi/grpc_test/cmake-3.18.0/Tests/CMakeBuildCOnly" --config Debug
  --clean-first --target COnly
  RESULT_VARIABLE RESULT)
if(RESULT)
  message(FATAL_ERROR "Error running cmake --build")
endif()

# run it again after clean
execute_process(COMMAND "${RUN_TEST}" RESULT_VARIABLE RESULT)
if(RESULT)
  message(FATAL_ERROR "Error running test COnly after clean ")
endif()
