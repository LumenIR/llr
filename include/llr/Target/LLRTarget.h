//===- llr/Target/LLRTarget.h - LLR Target --------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_LLRTARGET_H
#define LLR_TARGET_LLRTARGET_H

#include "llvm/ADT/Triple.h"

#include <memory>

namespace llr
{

class LLRContext;
class Interpreter;

class LLRTarget {
protected:
  LLRTarget(
      llvm::Triple Triple,
      LLRContext *ctx,
      Interpreter *interp
      ) :
    TargetTriple(Triple),
    Ctx_ptr(ctx),
    Interpreter_ptr(interp) {

  }

public:

  virtual ~LLRTarget() = default;

  LLRContext &getContext() const {
    return *Ctx_ptr;
  }


  Interpreter &getInterpeter() const {
    return *Interpreter_ptr;
  }

  const llvm::Triple &getTargetTriple() const {
    return TargetTriple;
  }


private:
  const llvm::Triple TargetTriple;


  LLRContext* Ctx_ptr;
  Interpreter* Interpreter_ptr;


}; // class LLRTarget

} // end namespace llr

#endif //LLR_TARGET_LLRTARGET_H
