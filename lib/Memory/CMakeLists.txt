add_llr_library(llrMemory
  Memory.cpp
  MemoryAccessResult.cpp
  MemoryBlock.cpp
  MemoryDispatcher.cpp
  SimpleMemory.cpp


  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support

  LINK_LIBS
)
