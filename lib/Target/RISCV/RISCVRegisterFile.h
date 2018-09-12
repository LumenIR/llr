//===- lib/Target/RISCV/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVREGISTERFILE_H
#define LLR_TARGET_RISCV_RISCVREGISTERFILE_H

#include "llr/Registers/RegisterFile.h"

#define GET_REGINFO_ENUM
#include "RISCVGenRegisterInfo.inc"
#undef GET_REGINFO_ENUM


namespace llr {

class RegisterBank;
class LLRRegister;

class RISCVRegisterFile : public RegisterFile {
public:
  RISCVRegisterFile();

  virtual ~RISCVRegisterFile() = default;

  virtual LLRRegister& getRegisterById(unsigned RegisterId) const override;

protected:
//  RegisterBank &GPRRegisters;
//  RegisterBank &SpecialRegisters;

  LLRRegister *PC;
  LLRRegister *SP;
  LLRRegister *FP;



}; // class RegisterFile

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVREGISTERFILE_H

