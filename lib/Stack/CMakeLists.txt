add_llr_library(llrStack
  StackBase.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Stack

  LINK_COMPONENTS
    Support

  LINK_LIBS
    llrMemory
    llrRegisters
)
