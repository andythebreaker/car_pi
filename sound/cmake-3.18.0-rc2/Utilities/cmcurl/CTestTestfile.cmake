# CMake generated Testfile for 
# Source directory: /home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Utilities/cmcurl
# Build directory: /home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Utilities/cmcurl
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("curl" "curltest" "http://open.cdash.org/user.php")
set_tests_properties(curl PROPERTIES  _BACKTRACE_TRIPLES "/home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Utilities/cmcurl/CMakeLists.txt;1346;add_test;/home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Utilities/cmcurl/CMakeLists.txt;0;")
subdirs("lib")
