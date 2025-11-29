cmake_minimum_required(VERSION 3.31)
project(lib42 C)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_PRERELEASE alpha)

set(CMAKE_C_STANDARD 17)

# Use GNUInstallDirs for standard installation directories
include(GNUInstallDirs)

# Optional coverage build. When enabled the project will be compiled with
# coverage instrumentation so gcov/lcov can capture coverage data. This should
# only be enabled on GCC/Clang toolchains.
option(CODE_COVERAGE "Enable coverage build (adds --coverage flags)" OFF)

if(CODE_COVERAGE)
  # Coverage requires tests to be built
  set(BUILD_TESTING ON CACHE BOOL "Build tests" FORCE)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Building with coverage instrumentation enabled")
    # Use -O0 to avoid optimization removing code paths; include debug info.
    add_compile_options(-O0 -g --coverage)
    # Ensure linker also uses coverage option for executables/libraries
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
  else()
    message(WARNING "CODE_COVERAGE requested but compiler does not appear to be GCC/Clang; skipping coverage flags")
  endif()
endif()

file(GLOB_RECURSE SOURCES "src/*.c")

add_library(lib42_static STATIC ${SOURCES})
set_target_properties(lib42_static PROPERTIES OUTPUT_NAME "42")

add_library(lib42_shared SHARED ${SOURCES})
set_target_properties(lib42_shared PROPERTIES OUTPUT_NAME "42")

target_include_directories(lib42_static PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(lib42_shared PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Enable warnings as errors for GCC/Clang
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(lib42_static PRIVATE -Wall -Wextra -Werror)
  target_compile_options(lib42_shared PRIVATE -Wall -Wextra -Werror)
endif()

# --- Tests (Criterion) -----------------------------------------------------
enable_testing()

# On macOS with Homebrew, help CMake/pkg-config find Criterion
if(APPLE)
  execute_process(
    COMMAND brew --prefix
    OUTPUT_VARIABLE HOMEBREW_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(HOMEBREW_PREFIX)
    list(APPEND CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}")
    set(ENV{PKG_CONFIG_PATH} "${HOMEBREW_PREFIX}/lib/pkgconfig:${HOMEBREW_PREFIX}/opt/criterion/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
  endif()
endif()

if(BUILD_TESTING)
  # Try to locate Criterion (C unit testing framework). This will allow building
  # a `lib42_tests` executable that links against the library and runs tests via ctest.
  find_package(Criterion QUIET)
  if(NOT Criterion_FOUND)
    message(STATUS "Criterion not found via CMake config; trying pkg-config...")
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
      pkg_check_modules(CRITERION criterion)
      if(CRITERION_FOUND)
        add_compile_definitions(-DCRITERION_PKGCONFIG)
        set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIRS})
        set(CRITERION_LIBRARIES ${CRITERION_LIBRARIES})
        set(CRITERION_LIBRARY_DIRS ${CRITERION_LIBRARY_DIRS})
      endif()
    endif()
  endif()

  if(Criterion_FOUND OR CRITERION_FOUND)
    # Collect tests
    file(GLOB_RECURSE TEST_SOURCES "tests/*.c")
    if(TEST_SOURCES)
      foreach(test_file ${TEST_SOURCES})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        target_include_directories(${test_name} PRIVATE include)
        # Link the library under test and Criterion
        if(TARGET Criterion::Criterion)
          target_link_libraries(${test_name} PRIVATE lib42_static Criterion::Criterion)
        else()
          target_include_directories(${test_name} PRIVATE ${CRITERION_INCLUDE_DIRS})
          if(CRITERION_LIBRARY_DIRS)
            target_link_directories(${test_name} PRIVATE ${CRITERION_LIBRARY_DIRS})
          endif()
          target_link_libraries(${test_name} PRIVATE lib42_static ${CRITERION_LIBRARIES})
        endif()
        add_test(NAME ${test_name} COMMAND ${test_name})
      endforeach()
    else()
      message(STATUS "No test sources found in tests/; skipping test target creation.")
    endif()
  else()
    message(STATUS "Criterion not found; skipping test target. Install Criterion to enable unit tests.")
  endif()
endif()

# --- Installation ---------------------------------------------------------
# Provide sane install rules so `cmake --install` actually installs the
# built libraries and the public headers. Without these `cmake --install`
# does nothing and the install_manifest will be empty.

# Install libraries (both static archive and shared library). Place libs in
# lib/ and runtime (soname) in lib/ as well; RUNTIME is used on Windows.
install(TARGETS lib42_static lib42_shared
  EXPORT lib42Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install the public include/ tree so consumers can find the headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
  PATTERN "macros.h" EXCLUDE
  PATTERN "*.int.h" EXCLUDE
)

# Optional: install a CMake export and a package config file so downstream
# projects can find the library via find_package(lib42). Keep it simple here.
install(EXPORT lib42Targets
  FILE lib42Targets.cmake
  NAMESPACE lib42::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lib42
)

# Generate a basic pkg-config file (optional). You can remove or improve
# this if you prefer not to install a pkg-config file.
set(_pc_file "${CMAKE_CURRENT_BINARY_DIR}/42.pc")
file(WRITE ${_pc_file} "prefix=${CMAKE_INSTALL_PREFIX}\n")
file(APPEND ${_pc_file} "libdir=")
file(APPEND ${_pc_file} "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\n")
file(APPEND ${_pc_file} "includedir=${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\n")
file(APPEND ${_pc_file} "\nName: lib42\nDescription: 42-style utility library\nVersion: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\n")
# Write variable references literally (escape ${} so CMake doesn't expand them)
file(APPEND ${_pc_file} "Libs: -L\${libdir} -l42\n")
file(APPEND ${_pc_file} "Cflags: -I\${includedir}\n")
install(FILES ${_pc_file} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# Doxygen documentation generation
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    doxygen-awesome-css
    URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
  )
  FetchContent_MakeAvailable(doxygen-awesome-css)

  # Save the location the files were cloned into
  # This allows us to get the path to doxygen-awesome.css
  FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

  # Generate the Doxyfile
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

  add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_BINARY_DIR}/doxygen/man/man3/_home_*
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )
else()
  message(STATUS "Doxygen not found; skipping documentation target.")
endif()
