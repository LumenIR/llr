add_llr_target(RISCV
  RISCVLLRDecoder.cpp
  RISCVLLRFetcher.cpp
  RISCVInterpreter.cpp
  RISCVTarget.cpp
  RISCVRegisterFile.cpp

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
