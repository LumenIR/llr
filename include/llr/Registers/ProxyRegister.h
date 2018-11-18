//===- llr/Registers/ProxyRegister.h - Proxy Register interface ---*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_PROXYREGISTER_H
#define LLR_REGISTERS_PROXYREGISTER_H

#include "LLRRegister.h"

#include "llvm/ADT/ArrayRef.h"

#include <vector>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {

class RegisterAccessResult;



class ProxyRegister : public LLRRegister {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;

public:

  ProxyRegister(const ProxyRegister&) = delete;
  ProxyRegister(ProxyRegister&&) = default;

  ProxyRegister(unsigned RegId, unsigned ClId, std::size_t size, uint8_t* storage_ptr) :
    LLRRegister(RegId, ClId, size),
    data_ptr(storage_ptr){
  }

  virtual RegisterAccessResult get() override;


  virtual RegisterAccessResult set(const llvm::ArrayRef<uint8_t> data, SetMode mode = SetMode::EXACT) override;

private:
  uint8_t* data_ptr;


}; // class ProxyRegister

} // end namespace llr

#endif //LLR_REGISTERS_PROXYREGISTER_H

