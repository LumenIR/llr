//===- llr/Context/Context.h - LLR execution context interface -*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_CONTEXT_LLRCONTEXT_H
#define LLR_CONTEXT_LLRCONTEXT_H

namespace llr
{

class Stack;
class Memory;
class LLRRegisterFile;

class LLRContext {

public:

  virtual ~LLRContext() = default;

  virtual Memory& getMemory() const = 0;

  virtual LLRRegisterFile& getRegisterFile() const = 0;

  virtual Stack& getStack() const = 0;

  virtual bool isRunning() const = 0;


}; // class LLRContext

} // end namespace llr

#endif //LLR_CONTEXT_LLRCONTEXT_H

