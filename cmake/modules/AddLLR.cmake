macro(add_llr_library name)
  cmake_parse_arguments(ARG
    "SHARED"
    ""
    ""
    ${ARGN})
  if(ARG_SHARED)
    set(ARG_ENABLE_SHARED SHARED)
  endif()
  llvm_add_library(${name} ${ARG_ENABLE_SHARED} ${ARG_UNPARSED_ARGUMENTS})
  set_target_properties(${name} PROPERTIES FOLDER "llr libraries")

  if (LLR_BUILD_TOOLS)
    if(${name} IN_LIST LLVM_DISTRIBUTION_COMPONENTS OR
        NOT LLVM_DISTRIBUTION_COMPONENTS)
      set(export_to_llrtargets EXPORT llrTargets)
      set_property(GLOBAL PROPERTY LLR_HAS_EXPORTS True)
    endif()

    install(TARGETS ${name}
      COMPONENT ${name}
      ${export_to_llrtargets}
      LIBRARY DESTINATION lib${LLVM_LIBDIR_SUFFIX}
      ARCHIVE DESTINATION lib${LLVM_LIBDIR_SUFFIX}
      RUNTIME DESTINATION bin)

    if (${ARG_SHARED} AND NOT CMAKE_CONFIGURATION_TYPES)
      add_custom_target(install-${name}
        DEPENDS ${name}
        COMMAND "${CMAKE_COMMAND}"
          -DCMAKE_INSTALL_COMPONENT=${name}
          -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
    endif()
    set_property(GLOBAL APPEND PROPERTY LLR_EXPORTS ${name})
  endif()
endmacro(add_llr_library)

macro(add_llr_executable name)
  add_llvm_executable(${name} ${ARGN})
  set_target_properties(${name} PROPERTIES FOLDER "llr executables")
endmacro(add_llr_executable)

macro(add_llr_tool name)
  if (NOT LLR_BUILD_TOOLS)
    set(EXCLUDE_FROM_ALL ON)
  endif()

  add_llr_executable(${name} ${ARGN})

  if (LLR_BUILD_TOOLS)
    if(${name} IN_LIST LLVM_DISTRIBUTION_COMPONENTS OR
        NOT LLVM_DISTRIBUTION_COMPONENTS)
      set(export_to_llrtargets EXPORT llrTargets)
      set_property(GLOBAL PROPERTY LLR_HAS_EXPORTS True)
    endif()

    install(TARGETS ${name}
      ${export_to_llrtargets}
      RUNTIME DESTINATION bin
      COMPONENT ${name})

    if(NOT CMAKE_CONFIGURATION_TYPES)
      add_custom_target(install-${name}
        DEPENDS ${name}
        COMMAND "${CMAKE_COMMAND}"
        -DCMAKE_INSTALL_COMPONENT=${name}
        -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
    endif()
    set_property(GLOBAL APPEND PROPERTY LLR_EXPORTS ${name})
  endif()
endmacro()

macro(add_llr_symlink name dest)
  add_llvm_tool_symlink(${name} ${dest} ALWAYS_GENERATE)
  # Always generate install targets
  llvm_install_symlink(${name} ${dest} ALWAYS_GENERATE)
endmacro()


macro(add_llr_target target_name)
  # TODO make it more reliable
  # CMAKE_CURRENT_BINARY_DIR
  # tools/llr/lib/Target/<Target>/
  # ->
  # lib/Target/<Target>

  include_directories(BEFORE
    ${CMAKE_CURRENT_BINARY_DIR}/../../../../../lib/Target/${target_name}
    ${CMAKE_CURRENT_SOURCE_DIR})
  add_llr_library(llrTarget${target_name} ${ARGN})
endmacro(add_llr_target)

