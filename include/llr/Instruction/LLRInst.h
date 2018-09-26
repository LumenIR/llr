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

#include "llvm/Support/raw_os_ostream.h"

#include "llvm/MC/MCInst.h"

#include <cassert>

namespace llvm {
class MCInst;

}

namespace llr {

class LLRContext;
class LLRRegister;

class LLROperand {
  enum LLROperandType : unsigned char {
    kInvalid,       ///< Uninitialized.
    kRegister,      ///< Register operand.
    kImmediate,     ///< Immediate operand.
    kFPImmediate,   ///< Floating-point immediate operand.
    kMemoryAddress  ///< MemoryAddress
  };
  LLROperandType Kind = kInvalid;

  union {
    int64_t ImmVal;
    double FPImmVal;
    LLRRegister* Register;
  };

public:
  bool isValid() const {
    return Kind != kInvalid;
  }

  bool isRegister() const {
    return Kind == kRegister;
  }

  bool isImm() const {
    return Kind == kImmediate;
  }

  bool isMemoryAddress() const {
    return Kind == kMemoryAddress;
  }

  LLRRegister & getRegister() const {
    assert(isRegister() && "This is not a register operand");
    return *Register;
  }

  int64_t getImm() const {
    assert(isImm() && "This is not a register operand");
    return ImmVal;
  }

  static LLROperand createRegisterOperand(LLRRegister *reg_ptr) {
    LLROperand op;
    op.Kind = kRegister;
    op.Register = reg_ptr;
    return op;
  }

  static LLROperand createImmOperand(int64_t imm) {
    LLROperand op;
    op.Kind = kImmediate;
    op.ImmVal = imm;
    return op;
  }
};


class LLRInst {
  using MCInst = llvm::MCInst;

public:
  LLRInst(MCInst, size_t Size, LLRContext&, void (*execution_func)(LLRContext &, LLRInst &));
  virtual ~LLRInst() = default;

  void execute(LLRContext &);

  const MCInst & getMCInst() const {
    return MCInstr;
  }

  size_t getSize() const { return Size; }

  unsigned getOpcode() const {
    return MCInstr.getOpcode();
  }

  unsigned getNumOperands() const {
    return operands.size();
  }

  LLROperand getOperand(size_t Idx) const {
    return operands[Idx];
  }

  void print(llvm::raw_ostream &OS) const;
  void dump() const;

private:
  const llvm::MCInst MCInstr;
  std::size_t Size;
  llvm::SmallVector<LLROperand, 8> operands;

  void (*execution_func)(LLRContext &, LLRInst &);

}; // class LLRInst



} // end namespace llr

#endif //LLR_INSTRUCTION_LLRINST_H
