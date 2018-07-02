add_llr_target(LumenIR
  LumenIRLLRDecoder.cpp
  LumenIRLLRFetcher.cpp
  LumenIRTarget.cpp
  LumenIRRegisterFile.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
    llrDecoder
    llrFetcher
    llrTarget
    llrInstruction
    llrMemory
    llrRegisters
)
