add_llr_library(llrTarget
  LLRTarget.cpp


  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
    llrContext
    llrInterpreter
)


add_subdirectory(LumenIR)
