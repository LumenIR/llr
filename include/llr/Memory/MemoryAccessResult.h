//===- llr/Memory/MemoryAccessResult.h - Memory access result -*- C++ -*  -===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_MEMORY_MEMORYACCESSRESULT_H
#define LLR_MEMORY_MEMORYACCESSRESULT_H

#include "llr/Memory/MemoryAddress.h"

#include "llvm/ADT/ArrayRef.h"

#include <vector>
#include <cassert>
#include <cstdint>

//namespace llvm {
//  class ArrayRef;
//}

namespace llr {

enum class MemoryAccessStatus {
  Forbidden,
  NotFound,
  Uninit,
  ReadOK,
  WriteOK
};


class MemoryAccessResult {
  using MAS = enum MemoryAccessStatus;
public:

  MemoryAccessResult(MAS S, MemoryAddress Addr) :
    Address(Addr),
    Status(S) {

  }


  MemoryAccessResult(MAS S, llvm::ArrayRef<uint8_t> d, MemoryAddress Address);


  MemoryAccessStatus getStatus() {
    return Status;
  }

  size_t getSize() const {
    return data.size();
  }

  llvm::ArrayRef<uint8_t> getData() const {
    assert(Status == MAS::ReadOK && "Trying to access data of failed memory read");
    return data;
  }

  const MemoryAddress & getAddress() const {
    return Address;
  }

public:
  MemoryAddress Address;
  MemoryAccessStatus Status;
  std::vector<uint8_t> data;

}; // class MemoryAccessResult

} // end namespace llr

#endif //LLR_MEMORY_MEMORYACCESSRESULT_H

