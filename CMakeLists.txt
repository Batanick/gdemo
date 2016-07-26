cmake_minimum_required(VERSION 2.8)
project(gdemo)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)

add_subdirectory(lib/glfw-3.2)
include_directories(lib/glfw-3.2/include)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
add_definitions(-DGLM_FORCE_RADIANS)

add_executable(gdemo ${SOURCE_FILES})

#static assets
file(COPY shaders DESTINATION ./)

#target_link_libraries(pong ${ASSIMP_LIB})
target_link_libraries(gdemo ${GLEW_LIBRARIES})
target_link_libraries(gdemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(gdemo glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

