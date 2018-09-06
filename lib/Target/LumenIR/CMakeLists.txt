add_llr_target(LumenIR
  LumenIRLLRDecoder.cpp
  LumenIRLLRFetcher.cpp
  LumenIRInterpreter.cpp
  LumenIRTarget.cpp
  LumenIRRegisterFile.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support
    MC

  LINK_LIBS
    llrContext
    llrDecoder
    llrFetcher
    llrTarget
    llrInstruction
    llrInterpreter
    llrMemory
    llrRegisters
)
