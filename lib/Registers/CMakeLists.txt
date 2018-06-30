add_llr_library(llrRegisters
  Register.cpp
  SimpleRegister.cpp

  ADDITIONAL_HEADER_DIRS
  $(LLR_INCLUDE_DIR)/llr/Registers

  LINK_COMPONENTS
    Support

  LINK_LIBS
)
