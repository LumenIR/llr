add_llr_library(llrMemory
  Memory.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support

  LINK_LIBS
)
