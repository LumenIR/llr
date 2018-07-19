add_custom_target(LLRUnitTests)
set_target_properties(LLRUnitTests PROPERTIES FOLDER "llr unit tests")

set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

# add_lld_unittest(test_dirname file1.cpp file2.cpp)
#
# Will compile the list of files together and link against llr
# Produces a binary named 'basename(test_dirname)'.
function(add_llr_unittest test_dirname)
  add_unittest(LLRUnitTests ${test_dirname} ${ARGN})
  target_link_libraries(${test_dirname} ${LLVM_COMMON_LIBS})
endfunction()

add_subdirectory(Memory)

