set(LLVM_LINK_COMPONENTS
  Support
  Object
)

add_llr_tool(llr
  llr.cpp
)

target_link_libraries(llr
  llrConfig
  llrMemory
  llrRegisters
)

install(TARGETS llr
  RUNTIME DESTINATION bin)

