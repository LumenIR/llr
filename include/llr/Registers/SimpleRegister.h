//===- llr/Registers/Register.h - Memory access interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_SIMPLEREGISTER_H
#define LLR_REGISTERS_SIMPLEREGISTER_H

#include "LLRRegister.h"

#include "llvm/ADT/ArrayRef.h"

#include <vector>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {

class RegisterAccessResult;



class SimpleRegister : public LLRRegister {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;

public:

  SimpleRegister(const SimpleRegister&) = delete;
  SimpleRegister(SimpleRegister&&) = default;

  SimpleRegister(unsigned RegId, unsigned ClId, std::size_t size) :
    LLRRegister(RegId, ClId, size) {
    data_storage.resize(size);
  }

  virtual RegisterAccessResult get() override;


  virtual RegisterAccessResult set(const llvm::ArrayRef<uint8_t> data, SetMode mode = SetMode::EXACT) override;

private:
  std::vector<uint8_t> data_storage;


}; // class SimpleRegister

} // end namespace llr

#endif //LLR_REGISTERS_SIMPLEREGISTER_H

