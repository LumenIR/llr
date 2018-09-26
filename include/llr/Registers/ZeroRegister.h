//===- llr/Registers/ZeroRegister.h - ZeroRegister -----------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_ZEROREGISTER_H
#define LLR_REGISTERS_ZEROREGISTER_H

#include "LLRRegister.h"

#include "llvm/ADT/ArrayRef.h"

#include <cstring>
#include <vector>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {

class RegisterAccessResult;



class ZeroRegister : public LLRRegister {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;

public:

  ZeroRegister(const ZeroRegister&) = delete;
  ZeroRegister(ZeroRegister&&) = default;

  ZeroRegister(unsigned RegId, unsigned ClId, std::size_t size) :
    LLRRegister(RegId, ClId, size) {
    data_storage.resize(size);
    std::fill(data_storage.begin(), data_storage.end(), 0);
  }

  virtual RegisterAccessResult get() override;


  virtual RegisterAccessResult set(const llvm::ArrayRef<uint8_t> data, SetMode mode = SetMode::EXACT) override;

private:
  std::vector<uint8_t> data_storage;
}; // class SimpleRegister

} // end namespace llr

#endif //LLR_REGISTERS_ZEROREGISTER_H

