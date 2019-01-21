find_package(SWIG REQUIRED)
include(UseSWIG)
set(CMAKE_SWIG_FLAGS "")

# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(../linked_list)

# Add swig module
set_property(SOURCE ../linked_list/linkedlist.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ../linked_list/linkedlist.i PROPERTY CMAKE_SWIG_FLAGS "-threads -includeall")

swig_add_library(LinkedList LANGUAGE python SOURCES ../linked_list/linkedlist.i ../linked_list/LinkedList.cpp)
swig_link_libraries(LinkedList ${PYTHON_LIBRARIES})

# Files to install with Python
set(PYTHON_INSTALL_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/LinkedList.py
        ${CMAKE_CURRENT_BINARY_DIR}/_LinkedList.so)

## Configure setup.py and copy to output directory
set(SETUP_PY_IN ../linked_list/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})

# Declare install target for python
#install(TARGETS swig_example
#        COMMAND "${PYTHON_EXECUTABLE} setup.py"
#        COMPONENT swig-python)

# Install target to call setup.py
add_custom_target(install-python
        DEPENDS LinkedList
        COMMAND python ${SETUP_PY_OUT} install)

add_custom_target(build-python
        DEPENDS LinkedList
        COMMAND python ${SETUP_PY_OUT} build)