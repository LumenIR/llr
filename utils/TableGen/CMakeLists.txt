set(LLVM_LINK_COMPONENTS Support)

add_tablegen(llr-tblgen LLR
  ExecutionFunctionMatcher.cpp
  TableGen.cpp
  )
set_target_properties(llr-tblgen PROPERTIES FOLDER "LLR tablegenning")