//===- lib/Target/LumenIR/LumenIRTarget.h - LLR LumenIR Target -*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_LUMENIR_LUMENIRTARGET_H
#define LLR_TARGET_LUMENIR_LUMENIRTARGET_H

#include "llr/Target/LLRTarget.h"


namespace llr
{

class Context;
class Interpeter;

class LumenIRLLRTarget : public LLRTarget {

public:
  LumenIRLLRTarget();


}; // class LLRTarget


//TODO make it static and create Target Register as in LLVM

std::unique_ptr<LLRTarget> createLumenIRLLRTarget();


} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRTARGET_H
