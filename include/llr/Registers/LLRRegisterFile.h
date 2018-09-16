//===- llr/Registers/LLRRegisterFile.h - RegisterFile interface-*- C++ -*-----===//
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

class LLRRegister;

class LLRRegisterFile {

public:

  LLRRegisterFile(LLRRegisterFile&) = delete;

  ~LLRRegisterFile() = default;

  LLRRegisterFile() = default;


  virtual LLRRegister& getRegisterById(unsigned RegisterId) const = 0;


}; // class LLRRegisterFile

} // end namespace llr

#endif //LLR_REGISTERS_LLRREGISTERFILE_H

