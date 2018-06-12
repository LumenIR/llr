//===- llr/Interpeter/Instruction.h ---- Instruction interface --*- C++ -*---=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_INSTRUCTION_LLRINST_H
#define LLR_INSTRUCTION_LLRINST_H

namespace llvm {
class MCInst;

}

namespace llr {

class Context;

class LLRInst {
  using MCInst = llvm::MCInst;

public:
  LLRInst(MCInst &);
  virtual ~LLRInst() = default;

  void execute(Context &);

  MCInst & getMCInst() const {
    return MCInstr;
  }

private:
  MCInst &MCInstr;

}; // class Instruction

} // end namespace llr

#endif //LLR_INSTRUCTION_LLRINST_H
