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

INSTALL(
	TARGETS Deve
	LIBRARY DESTINATION lib 
)
