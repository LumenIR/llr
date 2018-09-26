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
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/APSInt.h"


#include <cassert>

namespace llr {

enum class RegisterAccessStatus {
  RAS_Forbidden,
  RAS_ReadOk,
  RAS_WriteOk
};

class RegisterAccessResult {
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

  uint32_t asUint32() {
    assert(data_storage.size() == 4);
    return *reinterpret_cast<const uint32_t*>(getData().data());
  }

  int32_t asInt32() {
    assert(data_storage.size() == 4);
    return *reinterpret_cast<const int32_t*>(getData().data());
  }

  uint64_t asUint64() {
    assert(data_storage.size() == 8);
    return *reinterpret_cast<const uint64_t*>(getData().data());
  }

  int64_t asInt64() {
    assert(data_storage.size() == 8);
    return *reinterpret_cast<const int64_t*>(getData().data());
  }

  float asFloat() {
    assert(getSize() == 4);
    return  *reinterpret_cast<const float*>(getData().data());
  }

  double asDouble() {
    assert(getSize() == 8);
    return  *reinterpret_cast<const double *>(getData().data());
  }

  llvm::APInt asAPInt() {
    return llvm::APInt(getSize() * 8, llvm::ArrayRef<uint64_t>((const uint64_t*)getData().data(), getSize()/4));
  }

  llvm::APSInt asAPSInt() {
    return llvm::APSInt(asAPInt(), true);
  }

  llvm::APFloat asAPFloat() {
    assert(getSize() == 4 || getSize() == 8);

    if (getSize() == 4) {
        return llvm::APFloat(asFloat());
    } else if (getSize() == 8) {
        return llvm::APFloat(asDouble());
    }
  }

private:
  llvm::ArrayRef<uint8_t> data_storage;
  RegisterAccessStatus status;

}; // class RegisterAccessResult

} // end namespace llr

#endif //LLR_REGISTERS_REGISTERACCESSRESULT_H

