//===- llr/Memory/Memory.h - Memory access interface --------*- C++ -*0000-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_MEMORY_MEMORY_H
#define LLR_MEMORY_MEMORY_H

#include "llvm/ADT/ArrayRef.h"

#include <cstdint>

//namespace llvm {
//class ArrayRef;
//}

namespace llr {

class MemoryAccessResult;
class MemoryAddress;

class Memory {
  using ArrayRef = llvm::ArrayRef<uint8_t>;
  using size_t = std::size_t;

public:
  virtual ~Memory() = default;

  virtual MemoryAccessResult write(const MemoryAddress &Addr, const ArrayRef &data) = 0;
  virtual MemoryAccessResult read (const MemoryAddress &Addr, size_t size)   = 0;

}; // class Memory

} // end namespace llr

#endif //LLR_MEMORY_MEMORY_H

