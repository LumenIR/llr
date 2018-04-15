//===- llr/Memory/Memory.h - Memory access interface --------*- C++ -*0000-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_CONTEXT_CONTEXT_H
#define LLR_CONTEXT_CONTEXT_H

namespace llvm {
class ArrayRef;
}


namespace llr
{

class Memory;
class RegisterFile;

class Context {
  using ArrayRef = llvm::ArrayRef;
public:

  virtual ~Context() = default;

  virtual Memory& getMemory() const = 0;

  virtual RegisterFile& getRegisterFile() const = 0;


}; // class Memory

} // end namespace llr

#endif //LLR_CONTEXT_CONTEXT_H

