//===- llr/Registers/RegisterAccessResult.h - Memory access result-*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_REGISTERACCESSRESULT_H
#define LLR_REGISTERS_REGISTERACCESSRESULT_H

#include "llvm/ADT/ArrayRef.h"

#include <cassert>

namespace llvm {
  class APInt;
  class APFloat;
}

namespace llr {

enum class RegisterAccessStatus {
  RAS_Forbidden,
  RAS_ReadOk,
  RAS_WriteOk
};

class RegisterAccessResult {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;
  using RAS = llr::RegisterAccessStatus;

public:
  RegisterAccessResult(llvm::ArrayRef<uint8_t> data) :
    data_storage(data),
    status(RAS::RAS_ReadOk){
  }

  RegisterAccessResult(RAS status) :
    data_storage(),
    status(status) {
  }


  RegisterAccessStatus getStatus();
  size_t getSize() {
    return data_storage.size();
  }

  //TODO std::vector/array or llvm::SmallVector
  llvm::ArrayRef<uint8_t> getData() {
    assert(status == RAS::RAS_ReadOk && "Trying to get data from bad RegisterAccessResult");
    return data_storage;
  }

  //APFloat getAPFloat();
  //APInt getAPInt();

private:
  llvm::ArrayRef<uint8_t> data_storage;
  RegisterAccessStatus status;

}; // class RegisterAccessResult

} // end namespace llr

#endif //LLR_REGISTERS_REGISTERACCESSRESULT_H

