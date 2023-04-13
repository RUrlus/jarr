cmake_minimum_required(VERSION 3.16...3.25)
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)
set(CMAKE_MODULE_PATH_SAVED ${CMAKE_MODULE_PATH})
list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD ${JARR_CPP_STANDARD})
set(MNAME "_${PROJECT_NAME}_ext")
file(GLOB JARR_SRC_FILES "${PROJECT_SOURCE_DIR}/src/jarr-ext/src/*.cpp")
set(JARR_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/jarr-ext/include")

find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(${MNAME} MODULE ${JARR_SRC_FILES})
target_include_directories(${MNAME} PUBLIC ${JARR_INCLUDE_DIR})
target_link_libraries(${MNAME} PRIVATE pybind11::pybind11)

if(JARR_ENABLE_DEVMODE)
  target_compile_options(${MNAME} PRIVATE -Wall -Wextra -Wunused-variable -Wunused-const-variable)
endif()

# Set required C++ flags
set_property(TARGET ${MNAME} PROPERTY CXX_STANDARD ${JARR_CPP_STANDARD})
set_property(TARGET ${MNAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${MNAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

if(JARR_ADD_PYTHON_SUPPORT)
  find_package(Python3 COMPONENTS Development QUIET)
  if(NOT Python3_FOUND)
    find_package(Python3 COMPONENTS Development.Module REQUIRED)
  endif()
  target_link_libraries(${MNAME} PRIVATE Python3::Module)
endif()
if(JARR_ADD_NUMPY_SUPPORT)
  find_package(Python3 COMPONENTS NumPy REQUIRED)
  target_link_libraries(${MNAME} PRIVATE Python3::NumPy)
endif()
if(JARR_ADD_OPENMP_SUPPORT)
  find_package(OpenMP REQUIRED)
  target_compile_definitions(${MNAME} PRIVATE ${PROJECT_NAME}_HAS_OPENMP_SUPPORT=TRUE)
  target_link_libraries(${MNAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

if(JARR_MBUILD)
   set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/src")
endif()

install(TARGETS ${MNAME} LIBRARY DESTINATION "${PROJECT_NAME}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH_SAVED})
