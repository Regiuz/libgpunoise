project(libgpunoise)

SET( OGRE_INCLUDE_DIR "${OGRE_INCLUDE_DIR}" CACHE STRING
   "OGRE_INCLUDE_DIR" FORCE )
SET( OGRE_LIBS "${OGRE_LIBS}" CACHE STRING
   "OGRE_LIBS" FORCE ) # OIS;OgreMain
SET( OGRE_LIB_LINK_DIR "${OGRE_LIB_LINK_DIR}" CACHE STRING
   "OGRE_LIB_LINK_DIR" FORCE ) 

include_directories( ./include ${OGRE_INCLUDE_DIR} )




add_library(libgpunoise src/Add3D.cpp)





add_executable(demo demo/main.cpp demo/BaseApplication.cpp)

target_link_libraries(demo ${OGRE_LIBS} libgpunoise)





add_subdirectory(media)
add_subdirectory(include)
add_subdirectory(src)