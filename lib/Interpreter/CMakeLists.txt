add_llr_library(llrInterpreter
  LLRInterpreter.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Fetcher

  LINK_COMPONENTS
    Support

  LINK_LIBS
    llrFetcher
    llrInstruction
    llrContext
)
