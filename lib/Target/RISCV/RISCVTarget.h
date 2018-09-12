//===- lib/Target/RISCV/RISCVTarget.h - LLR RISCV Target -*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVTARGET_H
#define LLR_TARGET_RISCV_RISCVTARGET_H

#include "llr/Target/LLRTarget.h"


namespace llr
{

class LLRContext;
class Interpreter;

class RISCVLLRTarget : public LLRTarget {

public:
  RISCVLLRTarget(LLRContext *ctx, Interpreter *interp);
}; // class LLRTarget


} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVTARGET_H
