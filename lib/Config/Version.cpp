//===- lib/Config/Version.cpp - LLR Version Number ---------------*- C++-=====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines several version-related utility functions for LLD.
//
//===----------------------------------------------------------------------===//

#include "llr/Config/Version.h"

using namespace llvm;

// Returns an SVN repository path, which is usually "trunk".
static std::string getRepositoryPath() {
  StringRef S = LLR_REPOSITORY_STRING;
  size_t Pos = S.find("llr/");
  if (Pos != StringRef::npos)
    return S.substr(Pos + 4);
  return S;
}

// Returns an SVN repository name, e.g., " (trunk 284614)"
// or an empty string if no repository info is available.
static std::string getRepository() {
  std::string Repo = getRepositoryPath();
  std::string Rev = LLR_REVISION_STRING;

  if (Repo.empty() && Rev.empty())
    return "";
  if (!Repo.empty() && !Rev.empty())
    return " (" + Repo + " " + Rev + ")";
  return " (" + Repo + Rev + ")";
}

// Returns a version string, e.g., "LLR 4.0 (llr/trunk 284614)".
std::string llr::getLLRVersion() {
  return "LLR " + std::string(LLR_VERSION_STRING) + getRepository();
}
