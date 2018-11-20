set(LLVM_TARGET_DEFINITIONS ${LLVM_MAIN_SRC_DIR}/lib/Target/RISCV/RISCV.td)
tablegen(LLR RISCVGenExecutionFunctionMatcher.inc -gen-llr-execution-function-matcher -I${LLVM_MAIN_SRC_DIR}/lib/Target/RISCV)
add_public_tablegen_target(RISCVGenExecutionFunctionMatcher)

add_llr_target(RISCV
  RISCVLLRDecoder.cpp
  RISCVLLRExecutionFunctions.cpp
  RISCVLLRFetcher.cpp
  RISCVLLRInterpreter.cpp
  RISCVLLRTarget.cpp
  RISCVLLRRegisterFile.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Memory

  LINK_COMPONENTS
    Support
    MC

  DEPENDS
    RISCVGenExecutionFunctionMatcher

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
