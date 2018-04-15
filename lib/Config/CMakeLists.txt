add_llr_library(llrConfig
  Version.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLR_INCLUDE_DIR}/llr/Config

  LINK_COMPONENTS
    Support
)
