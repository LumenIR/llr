add_lld_library(llrDriver
  LlrDriver.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLR_INCLUDE_DIR}/llr/Driver

  LINK_COMPONENTS
    Support

  LINK_LIBS
)

