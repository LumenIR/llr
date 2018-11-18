# Check if lld is built as a standalone project.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(llr)
  cmake_minimum_required(VERSION 3.4.3)

  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(LLR_BUILT_STANDALONE TRUE)

  find_program(LLVM_CONFIG_PATH "llvm-config" DOC "Path to llvm-config binary")
  if(NOT LLVM_CONFIG_PATH)
    message(FATAL_ERROR "llvm-config not found: specify LLVM_CONFIG_PATH")
  endif()

  execute_process(COMMAND "${LLVM_CONFIG_PATH}"
                          "--obj-root"
                          "--includedir"
                          "--cmakedir"
                          "--src-root"
                  RESULT_VARIABLE HAD_ERROR
                  OUTPUT_VARIABLE LLVM_CONFIG_OUTPUT
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(HAD_ERROR)
    message(FATAL_ERROR "llvm-config failed with status ${HAD_ERROR}")
  endif()

  string(REGEX REPLACE "[ \t]*[\r\n]+[ \t]*" ";" LLVM_CONFIG_OUTPUT "${LLVM_CONFIG_OUTPUT}")

  list(GET LLVM_CONFIG_OUTPUT 0 OBJ_ROOT)
  list(GET LLVM_CONFIG_OUTPUT 1 MAIN_INCLUDE_DIR)
  list(GET LLVM_CONFIG_OUTPUT 2 LLVM_CMAKE_PATH)
  list(GET LLVM_CONFIG_OUTPUT 3 MAIN_SRC_DIR)

  set(LLVM_OBJ_ROOT ${OBJ_ROOT} CACHE PATH "path to LLVM build tree")
  set(LLVM_MAIN_INCLUDE_DIR ${MAIN_INCLUDE_DIR} CACHE PATH "path to llvm/include")
  set(LLVM_MAIN_SRC_DIR ${MAIN_SRC_DIR} CACHE PATH "Path to LLVM source tree")

  file(TO_CMAKE_PATH ${LLVM_OBJ_ROOT} LLVM_BINARY_DIR)

  if(NOT EXISTS "${LLVM_CMAKE_PATH}/LLVMConfig.cmake")
    message(FATAL_ERROR "LLVMConfig.cmake not found")
  endif()
  include("${LLVM_CMAKE_PATH}/LLVMConfig.cmake")

  list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_PATH}")

  set(PACKAGE_VERSION "${LLVM_PACKAGE_VERSION}")
  include_directories("${LLVM_BINARY_DIR}/include" ${LLVM_INCLUDE_DIRS})
  link_directories(${LLVM_LIBRARY_DIRS})

  set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib${LLVM_LIBDIR_SUFFIX})
  set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin)
  find_program(LLVM_TABLEGEN_EXE "llvm-tblgen" ${LLVM_TOOLS_BINARY_DIR} NO_DEFAULT_PATH)

  include(AddLLVM)
  include(TableGen)
  include(HandleLLVMOptions)
endif()

set(LLR_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LLR_INCLUDE_DIR ${LLR_SOURCE_DIR}/include )
set(LLR_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Compute the LLR version from the LLVM version.
string(REGEX MATCH "[0-9]+\\.[0-9]+(\\.[0-9]+)?" LLR_VERSION
  ${PACKAGE_VERSION})
message(STATUS "LLR version: ${LLR_VERSION}")

string(REGEX REPLACE "([0-9]+)\\.[0-9]+(\\.[0-9]+)?" "\\1" LLR_VERSION_MAJOR ${LLR_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9]+)(\\.[0-9]+)?" "\\1" LLR_VERSION_MINOR ${LLR_VERSION})

# Determine LLR revision and repository.
# TODO: Figure out a way to get the revision and the repository on windows.
if ( NOT CMAKE_SYSTEM_NAME MATCHES "Windows" )
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/utils/GetSourceVersion ${LLR_SOURCE_DIR}
                  OUTPUT_VARIABLE LLR_REVISION)

  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/utils/GetRepositoryPath ${LLR_SOURCE_DIR}
                  OUTPUT_VARIABLE LLR_REPOSITORY)
  if ( LLR_REPOSITORY )
    # Replace newline characters with spaces
    string(REGEX REPLACE "(\r?\n)+" " " LLR_REPOSITORY ${LLR_REPOSITORY})
    # Remove leading spaces
    STRING(REGEX REPLACE "^[ \t\r\n]+" "" LLR_REPOSITORY "${LLR_REPOSITORY}" )
    # Remove trailing spaces
    string(REGEX REPLACE "(\ )+$" "" LLR_REPOSITORY ${LLR_REPOSITORY})
  endif()

  if ( LLR_REVISION )
    # Replace newline characters with spaces
    string(REGEX REPLACE "(\r?\n)+" " " LLR_REVISION ${LLR_REVISION})
    # Remove leading spaces
    STRING(REGEX REPLACE "^[ \t\r\n]+" "" LLR_REVISION "${LLR_REVISION}" )
    # Remove trailing spaces
    string(REGEX REPLACE "(\ )+$" "" LLR_REVISION ${LLR_REVISION})
  endif()
endif ()

# Configure the Version.inc file.
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/llr/Config/Version.inc.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/llr/Config/Version.inc)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed. CMake would overwrite "
"the makefiles distributed with LLVM. Please create a directory and run cmake "
"from there, passing the path to this source directory as the last argument. "
"This process created the file `CMakeCache.txt' and the directory "
"`CMakeFiles'. Please delete them.")
endif()

list (APPEND CMAKE_MODULE_PATH "${LLR_SOURCE_DIR}/cmake/modules")

include(AddLLR)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NOT LLVM_INSTALL_TOOLCHAIN_ONLY)
  install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN ".svn" EXCLUDE
    PATTERN ".git" EXCLUDE
    )
endif()

add_subdirectory(utils/TableGen)

# All targets below may depend on all tablegen'd files.
get_property(LLR_TABLEGEN_TARGETS GLOBAL PROPERTY LLR_TABLEGEN_TARGETS)
add_custom_target(llr-tablegen-targets DEPENDS ${LLR_TABLEGEN_TARGETS})
set_target_properties(llr-tablegen-targets PROPERTIES FOLDER "Misc")
list(APPEND LLVM_COMMON_DEPENDS llr-tablegen-targets)

include_directories(third_party/elfio/include)

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(unittests)

