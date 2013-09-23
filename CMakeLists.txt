########################################################
# cmake file for building Marlin example Package
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################


# project name
PROJECT( Deve )


# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${PROJECT_NAME}_VERSION_MINOR 1 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )


FIND_PACKAGE( Marlin 1.0 ) # minimum required Marlin version
INCLUDE_DIRECTORIES( ${Marlin_INCLUDE_DIRS} )
LINK_LIBRARIES( ${Marlin_LIBRARIES} )
ADD_DEFINITIONS( ${Marlin_DEFINITIONS} )

# load root 
#SET( ROOT_USE_COMPONENTS 
#  Geom 
#  Eve 
#  RGL
#  EG)
FIND_PACKAGE( ROOT REQUIRED COMPONENTS Eve Geom RGL EG)
INCLUDE_DIRECTORIES( ${ROOT_INCLUDE_DIRS} )
LINK_LIBRARIES( ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})
ADD_DEFINITIONS( ${ROOT_DEFINITIONS} )

MESSAGE("check root     ---> ${ROOT_FOUND}")
MESSAGE("check Eve      ---> ${ROOT_EVE_FOUND}")
#load fastjet
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/)
find_package (fastjet REQUIRED)
INCLUDE_DIRECTORIES( ${FastJet_INCLUDE_DIRS} )
LINK_LIBRARIES( ${FastJet_LIBRARIES} )
ADD_DEFINITIONS( ${FastJet_DEFINITIONS} )

#load pythia8
#include(ReadBuildProperties)
#
#include(FindPythia8)
#
#IF(HEPMC_FOUND)
#  add_definitions(-DHEPMC_ENABLED)
#  include_directories(${HEPMC_INCLUDE})
#  set(LIBS ${LIBS} ${HEPMC_LIB})
#ENDIF(HEPMC_FOUND)


# optional package
#FIND_PACKAGE( AIDA )
#IF( AIDA_FOUND )
#  INCLUDE_DIRECTORIES( ${AIDA_INCLUDE_DIRS} )
#  LINK_LIBRARIES( ${AIDA_LIBRARIES} )
#  ADD_DEFINITIONS( "-DMARLIN_USE_AIDA" )
#  MESSAGE( STATUS "AIDA -- found" )
#ELSE()
#  MESSAGE( STATUS "AIDA -- not found" )
#ENDIF()



### DOCUMENTATION ###########################################################

OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" ON )

IF( INSTALL_DOC AND EXISTS "${PROJECT_SOURCE_DIR}/doc/CMakeLists.txt" )
    ADD_SUBDIRECTORY( ./doc )
ENDIF()



### LIBRARY #################################################################
#SET( ENV{CXXFLAGS} "-Wno-long-long $ENV{CXXFLAGS}" )
## require proper c and c++
## -pedantic cannot be set globally because it cannot be removed for certain
## source files only: grep pedantic src/CMakeLists.txt
#SET( ENV{CXXFLAGS} "-Wall -ansi $ENV{CXXFLAGS}" ) # FIXME -pedantic
#SET( ENV{CFLAGS} "-w -ansi -pedantic $ENV{CFLAGS}" ) # -w suppress all warning messages

ADD_DEFINITIONS( "-Wall -ansi -pedantic" )
ADD_DEFINITIONS( "-Wno-long-long" )
ADD_DEFINITIONS( "-Wno-sign-compare -fno-strict-aliasing" )

MACRO( ADD_FASTSIM_PKG _input_dir )
  MESSAGE( STATUS "Including package: ${_input_dir}" )
  INCLUDE_DIRECTORIES( BEFORE ${_input_dir}/include )
  SET(${PROJECT_NAME}_include_dir ${_input_dir}/include )
  AUX_SOURCE_DIRECTORY( ${_input_dir}/src ${PROJECT_NAME}_srcs )
ENDMACRO()

ADD_FASTSIM_PKG( ./source/EveDisplay )
#ADD_FASTSIM_PKG( ./source/EvePFO )
ADD_FASTSIM_PKG( ./source/EventLoader )

SET_SOURCE_FILES_PROPERTIES( 
  ${${PROJECT_NAME}_srcs} 
  PROPERTIES 
  COMPILE_FLAGS "-pedantic" )

ADD_SHARED_LIBRARY( ${PROJECT_NAME} ${${PROJECT_NAME}_srcs} )
INSTALL_SHARED_LIBRARY( ${PROJECT_NAME}  DESTINATION lib )

MESSAGE("INCLUDE_DIRECTORIES_a :::: ${INCLUDE_DIRECTORIES}")
MESSAGE("INCLUDE_DIRECTORIES_b :::: ${${PROJECT_NAME}_include_dir}")

ADD_SUBDIRECTORY( ./example )

DISPLAY_STD_VARIABLES()


