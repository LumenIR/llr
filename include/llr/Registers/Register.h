//===- llr/Registers/Register.h - Memory access interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_REGISTER_H
#define LLR_REGISTERS_REGISTER_H

#include "llvm/ADT/ArrayRef.h"

#include <cstdint>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {

class RegisterAccessResult;



class Register {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;

public:
  Register(const Register&) = delete;
  Register(Register&&) = default;
  virtual ~Register() = default;

protected:
  Register(unsigned RegId, unsigned ClId, std::size_t size) :
    RegisterId(RegId),
    ClassId(ClId),
    RegisterSize(size) {
  }

public:
  //llvm registers mapping
  unsigned getRegisterId();
  unsigned getRegisterClassId();

  virtual RegisterAccessResult get() = 0;

  enum class SetMode {
    /// llvm_unreachable if register size does not match data
    EXACT,
    /// llvm_unreachable if register size greater than data size
    ZEXT,
    SEXT
  };

  virtual RegisterAccessResult set(const llvm::ArrayRef<uint8_t> data, SetMode mode = SetMode::EXACT) = 0;

// TODO
//  RegisterAccessResult set(const APInt &IntValue, SetMode mode = SetMode::EXACT);
//  RegisterAccessResult set(const APFloat &FloatValue);

private:
  unsigned RegisterId;
  unsigned ClassId;

  std::size_t RegisterSize;
}; // class Register

} // end namespace llr

#endif //LLR_REGISTERS_REGISTER_H

