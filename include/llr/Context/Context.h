//===- llr/Context/Context.h - Memory access interface --------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_CONTEXT_CONTEXT_H
#define LLR_CONTEXT_CONTEXT_H

namespace llr
{

class Stack;
class Memory;
class RegisterFile;

class Context {

public:

  virtual ~Context() = default;

  virtual Memory& getMemory() const = 0;

  virtual RegisterFile& getRegisterFile() const = 0;

  virtual Stack& getStack() const = 0;

  virtual bool isRunning() const = 0;


}; // class Memory

} // end namespace llr

#endif //LLR_CONTEXT_CONTEXT_H

