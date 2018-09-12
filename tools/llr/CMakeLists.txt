set(LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Support
  Object
  Target
)

add_llr_tool(llr
  llr.cpp
)

target_link_libraries(llr PRIVATE
  llrConfig
  llrContext
  llrDriver
  llrInterpreter
  llrMemory
  llrRegisters
  llrTarget
  llrTargetRISCV
)

install(TARGETS llr
  RUNTIME DESTINATION bin)

