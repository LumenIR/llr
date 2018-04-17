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
  using ArrayRef = llvm::ArrayRef<uint8_t>;
public:
  MemoryAccessResult(MAS S) {
    Stat = S;
  }

  MemoryAccessStatus getStatus() {
    return Stat;
  }

  size_t getSize() {
    return data.size();
  }

  ArrayRef getData() {
    assert(Stat == MAS::ReadOK && "Trying to access data of failed memory read");
    return data;
  }

public:
  MemoryAccessStatus Stat;
  std::vector<uint8_t> data;

}; // class MemoryAccessResult

} // end namespace llr

#endif //LLR_MEMORY_MEMORYACCESSRESULT_H

