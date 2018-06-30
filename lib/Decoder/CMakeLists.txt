add_llr_library(llrDecoder
  LLRDecoder.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Context

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
    llrInstruction
)
