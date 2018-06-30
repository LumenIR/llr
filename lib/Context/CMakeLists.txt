add_llr_library(llrContext
  LLRContext.cpp
  LLRContextBase.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Context

  LINK_COMPONENTS
    Support

  LINK_LIBS
    llrMemory
    llrRegisters
    llrStack
)
