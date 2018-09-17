//===- llr/Registers/LLRRegister.h - Register access interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_LLRREGISTER_H
#define LLR_REGISTERS_LLRREGISTER_H

#include "llr/Registers/RegisterAccessResult.h"
#include "llvm/ADT/ArrayRef.h"

#include <cstdint>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {




class LLRRegister {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;

public:
  LLRRegister(const LLRRegister&) = delete;
  LLRRegister(LLRRegister&&) = default;
  virtual ~LLRRegister() = default;

protected:
  LLRRegister(unsigned RegId, unsigned ClId, std::size_t size) :
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


  virtual RegisterAccessResult set(uint32_t data, SetMode mode = SetMode::EXACT) final {
    set(llvm::ArrayRef<uint8_t>(reinterpret_cast<uint8_t*>(&data), 4), mode);
  }

  virtual RegisterAccessResult set(uint64_t data, SetMode mode = SetMode::EXACT) final {
    set(llvm::ArrayRef<uint8_t>(reinterpret_cast<uint8_t*>(&data), 8), mode);
  }



// TODO
//  RegisterAccessResult set(const APInt &IntValue, SetMode mode = SetMode::EXACT);
//  RegisterAccessResult set(const APFloat &FloatValue);

protected:
  unsigned RegisterId;
  unsigned ClassId;

  std::size_t RegisterSize;
}; // class LLRRegister

} // end namespace llr

#endif //LLR_REGISTERS_LLRREGISTER_H

