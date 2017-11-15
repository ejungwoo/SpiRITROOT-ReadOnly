cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(SpiRITROOT-ReadOnly)

list(APPEND PRJ_SOURCE_DIRECTORY_LIST
  source/format/
  source/global/
)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net Eve Geom Gui Graf Graf3d Ged RGL Matrix MathCore)

include(${ROOT_USE_FILE})

foreach(_directory ${PRJ_SOURCE_DIRECTORY_LIST})
  include_directories(${CMAKE_SOURCE_DIR}/${_directory})
  string(REPLACE / _ _name ${_directory})
  list(APPEND PRJ_SOURCE_NAME_LIST ${_name})
  set(PRJ_${_name}_G_NAME G__${_name}Dict)
  file(GLOB PRJ_${_name}_LINKDEF_FILE ${CMAKE_SOURCE_DIR}/${_directory}/LinkDef.h)
  file(GLOB PRJ_${_name}_SOURCE_FILES ${CMAKE_SOURCE_DIR}/${_directory}/*cc)
  file(GLOB PRJ_${_name}_HEADER_FILES ${CMAKE_SOURCE_DIR}/${_directory}/*hh)
endforeach(_directory)

include_directories(${CMAKE_SOURCE_DIR}/log)
add_definitions(${ROOT_CXX_FLAGS})

foreach(_name ${PRJ_SOURCE_NAME_LIST})
  ROOT_GENERATE_DICTIONARY(${PRJ_${_name}_G_NAME}
    ${PRJ_${_name}_HEADER_FILES}
    LINKDEF ${PRJ_${_name}_LINKDEF_FILE}
  )
endforeach(_name)

foreach(_name ${PRJ_SOURCE_NAME_LIST})
  foreach(_file ${PRJ_${_name}_SOURCE_FILES})
    list(APPEND PRJ_LIB_LIST ${_file})
  endforeach(_file)
  list(APPEND PRJ_LIB_LIST ${PRJ_${_name}_G_NAME}.cxx)
endforeach(_name)

add_library(SpiRIROOT-ReadOnly SHARED ${PRJ_LIB_LIST})
target_link_libraries(SpiRIROOT-ReadOnly ${ROOT_LIBRARIES})
