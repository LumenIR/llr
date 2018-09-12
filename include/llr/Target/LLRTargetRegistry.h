//===- llr/Target/LLRTargetRegistry.h - LLR Target Registry ----*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_LLRTARGETREGISTRY_H
#define LLR_TARGET_LLRTARGETREGISTRY_H

#include "llvm/ADT/Triple.h"

#include <memory>

namespace llr
{

class LLRTarget;

namespace registry {


#define LLR_TARGET(TargetName) LLRInitialize##TargetName##Target();

extern "C" void LLR_TARGET(RISCV);

inline void InitializeAllLLRTargets() {
  LLR_TARGET(RISCV)

  //TODO init LLR from generated list
  //#include "llvm/Config/Targets.def"
}

#undef LLR_TARGET

void registerTarget(llvm::Triple, LLRTarget*(func)());

LLRTarget * getLLRTarget(llvm::Triple);


} // end namespase registry

} // end namespace llr

#endif //LLR_TARGET_LLRTARGETREGISTRY_H
