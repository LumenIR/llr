//===- llr/Registers/Register.h - Memory access interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_REGISTERCLASS_H
#define LLR_REGISTERS_REGISTERCLASS_H

#include "llr/Registers/Register.h"

#include "llvm/ADT/ArrayRef.h"

namespace llr {


class RegisterClass {
  RegisterClass(RegisterClass) = delete;
  virtual ~RegisterClass() = default;


public:
  virtual Register& getRegister(size_t regIdx) = 0;

protected:



}; // class RegisterClass

} // end namespace llr

#endif //LLR_REGISTERS_REGISTERCLASS_H
