project(libgpunoise)

SET( OGRE_INCLUDE_DIR "${OGRE_INCLUDE_DIR}" CACHE STRING
   "OGRE_INCLUDE_DIR" FORCE )
SET( OGRE_LIBS "${OGRE_LIBS}" CACHE STRING
   "OGRE_LIBS" FORCE ) # OIS;OgreMain
SET( OGRE_LIB_LINK_DIR "${OGRE_LIB_LINK_DIR}" CACHE STRING
   "OGRE_LIB_LINK_DIR" FORCE ) 

include_directories( ./include ${OGRE_INCLUDE_DIR} )




add_library(libgpunoise
  #other
  src/Module.cpp
  src/Module3D.cpp
  src/MPPerlinHelper.cpp
  src/BinaryCGFunction3D.cpp
  src/BinaryCGOperator3D.cpp
  src/BinaryCombiner3D.cpp


  #modifiers
  src/Abs3D.cpp
  src/Clamp3D.cpp
  
  #generators
  src/MPPerlin3D.cpp
  src/Perlin3D.cpp
  src/Voronoi3D.cpp

  #combiners
  src/Add3D.cpp
  src/Multiply3D.cpp
  src/Min3D.cpp
  src/Max3D.cpp
  src/Power3D.cpp
)





add_executable(demo demo/main.cpp demo/BaseApplication.cpp)

target_link_libraries(demo ${OGRE_LIBS} libgpunoise)





add_subdirectory(media)
add_subdirectory(include)
add_subdirectory(src)