add_llr_library(llrFetcher
  LLRFetcher.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Context

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
    llrContext
    llrMemory
    llrRegisters
)
