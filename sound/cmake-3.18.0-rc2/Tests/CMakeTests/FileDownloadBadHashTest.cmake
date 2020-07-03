if(NOT "/home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Tests/CMakeTests" MATCHES "^/")
  set(slash /)
endif()
set(url "file://${slash}/home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Tests/CMakeTests/FileDownloadInput.png")
set(dir "/home/wp2018/user/andythebreaker/andy/sound/cmake-3.18.0-rc2/Tests/CMakeTests/downloads")

file(DOWNLOAD
  ${url}
  ${dir}/file3.png
  TIMEOUT 2
  STATUS status
  EXPECTED_HASH SHA1=5555555555555555555555555555555555555555
  )
