add_llr_library(llrInstruction
  LLRInst.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Instruction

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
)

