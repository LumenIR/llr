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

class LLRContext;
class Interpreter;

class LumenIRLLRTarget : public LLRTarget {

public:
  LumenIRLLRTarget(LLRContext *ctx, Interpreter *interp);
}; // class LLRTarget


} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRTARGET_H
