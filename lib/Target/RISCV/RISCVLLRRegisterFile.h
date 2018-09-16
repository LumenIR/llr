//===- lib/Target/RISCV/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H
#define LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H

#include "llr/Registers/LLRRegisterFile.h"

#define GET_REGINFO_ENUM
#include "RISCVGenRegisterInfo.inc"
#undef GET_REGINFO_ENUM


namespace llr {

class LLRRegister;

class RISCVLLRRegisterFile : public LLRRegisterFile {
public:
  RISCVLLRRegisterFile();

  virtual ~RISCVLLRRegisterFile() = default;

  virtual LLRRegister& getRegisterById(unsigned RegisterId) const override;

protected:
  LLRRegister *PC;
  LLRRegister *SP;
  LLRRegister *FP;



}; // class RISCVLLRRegisterFile

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H

