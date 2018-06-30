add_llr_target(LumenIR
  LumenIRTarget.cpp
  LumenIRRegisterFile.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support

  LINK_LIBS
    llrTarget
    llrMemory
    llrRegisters
)
