# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AutoClick_autogen"
  "CMakeFiles\\AutoClick_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AutoClick_autogen.dir\\ParseCache.txt"
  )
endif()
