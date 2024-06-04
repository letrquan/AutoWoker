# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "AutoWorker_autogen"
  "CMakeFiles\\AutoWorker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AutoWorker_autogen.dir\\ParseCache.txt"
  )
endif()
