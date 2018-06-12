//===- llr/Stack/Stack.h - Stack interface --------------------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_STACK_STACK_H
#define LLR_STACK_STACK_H

#include "llr/Stack/Stack.h"

namespace llvm {

class ArrayRef;

}

namespace llr {

class MemoryAccessResult;
class Memory;
class RegisterFile;


class StackBase : public Stack {
  using ArrayRef = llvm::ArrayRef;

public:
  StackBase(Memory *, RegisterFile *);

protected:
  Memory *Mem;
  RegisterFile *RegFile;

}; // class Stack

} // end namespace llr

#endif //LLR_STACK_STACK_H
