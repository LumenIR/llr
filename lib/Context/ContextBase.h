//===- llr/lib/Context/ContextBase.h - Context Base Class ----*- C++ -*----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_LIB_CONTEXT_CONTEXTBASE_H
#define LLR_LIB_CONTEXT_CONTEXTBASE_H

#include "llr/Context/Context.h"

namespace llr
{

class Memory;
class RegisterFile;
class Stack;

class ContextBase : public Context {

public:
  ContextBase(Memory *, RegisterFile *, Stack *);

  virtual Memory& getMemory() const override;

  virtual RegisterFile& getRegisterFile() const override;

  virtual Stack& getStack() const override;

private:
  Memory *Mem_ptr;
  RegisterFile *RegisterFile_ptr;
  Stack *Stack_ptr;

}; // class ContextBase

} // end namespace llr

#endif //LLR_LIB_CONTEXT_CONTEXTBASE_H

