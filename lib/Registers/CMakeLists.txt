add_llr_library(llrRegisters
  LLRRegister.cpp
  ProxyRegister.cpp
  SimpleRegister.cpp
  ZeroRegister.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Registers

  LINK_COMPONENTS
    Support

  LINK_LIBS
)
