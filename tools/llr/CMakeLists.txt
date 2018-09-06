set(LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Support
  Object
  Target
)

add_llr_tool(llr
  llr.cpp
)

target_link_libraries(llr
  llrConfig
  llrContext
  llrDriver
  llrInterpreter
  llrMemory
  llrRegisters
  llrTarget
  llrTargetLumenIR
)

install(TARGETS llr
  RUNTIME DESTINATION bin)

