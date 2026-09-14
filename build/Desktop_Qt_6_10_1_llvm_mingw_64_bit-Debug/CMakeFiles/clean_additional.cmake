# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MotoCluster_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MotoCluster_autogen.dir\\ParseCache.txt"
  "MotoCluster_autogen"
  )
endif()
