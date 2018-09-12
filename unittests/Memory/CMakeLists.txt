
add_llr_unittest(llrMemoryTests
  SimpleMemoryManagerTests.cpp
)

target_link_libraries(llrMemoryTests
PRIVATE
  llrMemory
)
