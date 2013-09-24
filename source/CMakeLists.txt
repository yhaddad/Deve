#######################################################
# cmake file for building Deve package
# @author Eté Rémi 
#######################################################

# include directories
INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( BEFORE "${PROJECT_BINARY_DIR}" ) # generated DeveConfig.h


# require proper c++
ADD_DEFINITIONS( "-pedantic -Wunused-value -O2" )
ADD_DEFINITIONS("-Wno-long-long")


# create library	
FILE (
	GLOB_RECURSE
	DEVE_LIBRARY_FILES
	include/*
	src/*
)

ADD_SHARED_LIBRARY( Deve ${DEVE_LIBRARY_FILES} )
TARGET_LINK_LIBRARIES( Deve  ${ROOT_COMPONENT_LIBRARIES} )

ADD_EXECUTABLE( Deve_bin main/Deve.cc )
TARGET_LINK_LIBRARIES( Deve_bin Deve )
SET_TARGET_PROPERTIES( Deve_bin PROPERTIES OUTPUT_NAME Deve )


INSTALL(
	TARGETS Deve
	LIBRARY DESTINATION lib 
)


