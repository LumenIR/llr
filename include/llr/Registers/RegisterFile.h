//===- llr/Registers/Register.h - Memory access interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_REGISTERFILE_H
#define LLR_REGISTERS_REGISTERFILE_H


namespace llr {

class RegisterBank;

class RegisterFile {

  RegisterFile(RegisterFile&) = delete;

  ~RegisterFile() = default;

public:
  virtual RegisterBank& getRegisterBank(unsigned RegisterBankId) const = 0;


}; // class RegisterFile

} // end namespace llr

#endif //LLR_REGISTERS_REGISTERFILE_H

