# Created by liyingmin on 18-10-29.
# tested on CentOS7.5 Anaconda3 & Anaconda2
# also tested on original python env py2
cmake_minimum_required(VERSION 2.8)

option(ANACONDA_PYTHON_VERBOSE "Anaconda dependency info" OFF)

if(NOT CMAKE_FIND_ANACONDA_PYTHON_INCLUDED)
  set(CMAKE_FIND_ANACONDA_PYTHON_INCLUDED 1)

  # find anaconda installation
  set(_cmd conda info --root)
  execute_process(
    COMMAND ${_cmd}
    RESULT_VARIABLE _r
    OUTPUT_VARIABLE _o
    ERROR_VARIABLE _e
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    )
  
  if(ANACONDA_PYTHON_VERBOSE)
    message("Executing conda info --root")
    message("_r = ${_r}")
    message("_o = ${_o}")
    message("_e = ${_e}")
  endif()
  string (REGEX MATCH "anaconda([0-9]+)" ANACONDA_VERSION "${_o}")

  IF(IS_DIRECTORY ${_o})
     set(ANACONDA_PYTHON_FOUND True)
  endif()

  if(ANACONDA_PYTHON_FOUND)
    set( ANACONDA_PYTHON_DIR ${_o} )
    message( "Found anaconda root directory ${ANACONDA_PYTHON_DIR}" )

    # find python version
    #
    set(_cmd python --version)
    execute_process(
      COMMAND ${_cmd}
      RESULT_VARIABLE _r
      OUTPUT_VARIABLE _o
      ERROR_VARIABLE _e
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
      )
    
    if(ANACONDA_PYTHON_VERBOSE)
      message("Executing python --version")
      message("_r = ${_r}")
      message("_o = ${_o}")
      message("_e = ${_e}")
    endif()
    if( NOT DEFINED ENV{CONDA_DEFAULT_ENV} )
      set( env_CONDA_DEFAULT_ENV "root" )
    else()
      set( env_CONDA_DEFAULT_ENV $ENV{CONDA_DEFAULT_ENV} )
    endif()
    if(${ANACONDA_VERSION} MATCHES 2)
      if( env_CONDA_DEFAULT_ENV STREQUAL "root" OR env_CONDA_DEFAULT_ENV STREQUAL "base")
        string (REGEX MATCH "Python ([0-9]+)[.]([0-9]+)[.]([0-9]+)" _py_version_found "${_e}")
      else()
        string (REGEX MATCH "Python ([0-9]+)[.]([0-9]+)[.]([0-9]+)" _py_version_found "${_o}")
      endif()
    else()
      if( env_CONDA_DEFAULT_ENV STREQUAL "root" OR env_CONDA_DEFAULT_ENV STREQUAL "base")
        string (REGEX MATCH "Python ([0-9]+)[.]([0-9]+)[.]([0-9]+)" _py_version_found "${_o}")
      else()
        string (REGEX MATCH "Python ([0-9]+)[.]([0-9]+)[.]([0-9]+)" _py_version_found "${_e}")
      endif()
    endif()
    message("_py_version_found = ${_py_version_found}")
    message("CMAKE_MATCH_0 = ${CMAKE_MATCH_0}")
    set( _py_version_major ${CMAKE_MATCH_1} )
    set( _py_version_minor ${CMAKE_MATCH_2} )
    set( _py_version_patch ${CMAKE_MATCH_3} )
    set( ANACONDA_PYTHON_VERSION ${_py_version_major}.${_py_version_minor} )

    
    if( ${_py_version_major} MATCHES 2 )
      set( _py_ext "")
    else()
      set( _py_ext "m")
    endif()

    set(_py_id "python${ANACONDA_PYTHON_VERSION}${_py_ext}")
    set(_py_id_no_m "python${ANACONDA_PYTHON_VERSION}")
    message( "Using anaconda ${env_CONDA_DEFAULT_ENV} environment" )
    if( env_CONDA_DEFAULT_ENV STREQUAL "root" OR env_CONDA_DEFAULT_ENV STREQUAL "base")
      set(PYTHON_INCLUDE_DIR "${ANACONDA_PYTHON_DIR}/include/${_py_id}" CACHE INTERNAL "")
      set(PYTHON_LIBRARY "${ANACONDA_PYTHON_DIR}/lib/lib${_py_id}${CMAKE_SHARED_LIBRARY_SUFFIX}" CACHE INTERNAL "")
      set(PYTHON_OUTPUT_PACKAGE_DIR "${ANACONDA_PYTHON_DIR}/lib/${_py_id_no_m}" PARENT_SCOPE)
    else()
      set(PYTHON_INCLUDE_DIR "${ANACONDA_PYTHON_DIR}/envs/${env_CONDA_DEFAULT_ENV}/include/${_py_id}" CACHE INTERNAL "")
      set(PYTHON_LIBRARY "${ANACONDA_PYTHON_DIR}/envs/${env_CONDA_DEFAULT_ENV}/lib/lib${_py_id}${CMAKE_SHARED_LIBRARY_SUFFIX}" CACHE INTERNAL "")
      set(PYTHON_OUTPUT_PACKAGE_DIR "${ANACONDA_PYTHON_DIR}/envs/${env_CONDA_DEFAULT_ENV}/lib/${_py_id_no_m}" PARENT_SCOPE)
    endif()

    set(PYTHON_INCLUDE_DIRS "${PYTHON_INCLUDE_DIR}")
    set(PYTHON_LIBRARIES "${PYTHON_LIBRARY}")

    set(FOUND_PYTHONLIBS TRUE)
  else()
    message( "Not found: anaconda root directory..." )
    message( "Trying system python install..." )
    find_package(PythonLibs)
    message(STATUS "PYTHON_LIBRARIES = " ${PYTHON_LIBRARIES})
    message(STATUS "PYTHON_INCLUDE_PATH = " ${PYTHON_INCLUDE_PATH})
    message(STATUS "PYTHON_INCLUDE_DIRS = " ${PYTHON_INCLUDE_DIRS})
    message(STATUS "PYTHONLIBS_VERSION_STRING = " ${PYTHONLIBS_VERSION_STRING})
    string (REGEX MATCH "python([0-9]+)[.]([0-9]+)" _py_version "${PYTHON_INCLUDE_DIRS}")
    message(STATUS "PYTHON_VERSION = ${_py_version}")
    set(PYTHON_OUTPUT_PACKAGE_DIR "/usr/lib/${_py_version}/site-packages" PARENT_SCOPE)
  endif()
  
  message( "PYTHON_INCLUDE_DIR = ${PYTHON_INCLUDE_DIR}")
  message( "PYTHON_LIBRARY = ${PYTHON_LIBRARY}")
endif()

