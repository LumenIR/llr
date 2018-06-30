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

class Context;
class Interpeter;

class LLRTarget {
protected:
  LLRTarget(
      llvm::Triple Triple,
      Context *ctx,
      Interpeter *interp
      ) :
    TargetTriple(Triple),
    Ctx_ptr(ctx),
    Interpeter_ptr(interp) {

  }

public:

  virtual ~LLRTarget() = default;

  Context &getContext() const {
    return *Ctx_ptr;
  }


  Interpeter &getInterpeter() const {
    return *Interpeter_ptr;
  }

  const llvm::Triple &getTargetTriple() const {
    return TargetTriple;
  }


private:
  const llvm::Triple TargetTriple;


  Context* Ctx_ptr;
  Interpeter* Interpeter_ptr;


}; // class LLRTarget

} // end namespace llr

#endif //LLR_TARGET_LLRTARGET_H
