//===- lib/Target/LumenIR/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_LUMENIR_LUMENIRREGISTERFILE_H
#define LLR_TARGET_LUMENIR_LUMENIRREGISTERFILE_H

#include "llr/Registers/RegisterFile.h"

#define GET_REGINFO_ENUM
#include "LumenIRGenRegisterInfo.inc"
#undef GET_REGINFO_ENUM


namespace llr {

class RegisterBank;
class LLRRegister;

class LumenIRRegisterFile : public RegisterFile {
public:
  LumenIRRegisterFile();

  virtual ~LumenIRRegisterFile() = default;

  virtual LLRRegister& getRegisterById(unsigned RegisterId) const override;

protected:
//  RegisterBank &GPRRegisters;
//  RegisterBank &SpecialRegisters;

  LLRRegister *PC;
  LLRRegister *SP;
  LLRRegister *FP;



}; // class RegisterFile

} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRREGISTERFILE_H

