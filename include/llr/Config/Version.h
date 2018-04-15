//===- llr/Config/Version.h - LLD Version Number ----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Defines a version-related utility function.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_VERSION_H
#define LLR_VERSION_H

#include "llr/Config/Version.inc"
#include "llvm/ADT/StringRef.h"

namespace llr {
/// \brief Retrieves a string representing the complete llr version.
std::string getLLRVersion();
}

#endif // LLR_VERSION_H
