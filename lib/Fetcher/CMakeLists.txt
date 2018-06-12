add_llr_library(llrFetcher
  Fetcher.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Context

  LINK_COMPONENTS
    Support

  LINK_LIBS
    llrContext
    llrMemory
    llrRegisters
)
