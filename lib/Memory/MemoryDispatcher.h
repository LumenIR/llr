//===- llr/lib/Memory/Memory.h - Memory dispatcher --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_LIB_MEMORY_MEMORYDISPATCHER_H
#define LLR_LIB_MEMORY_MEMORYDISPATCHER_H

#include "llr/Memory/Memory.h"

#include "llvm/ADT/IntervalMap.h"

#include <cstdint>

namespace llr {

class MemoryAccessResult;
class MemoryAddress;

class MemoryDispatcher : public Memory {
  using ArrayRef = llvm::ArrayRef<uint8_t>;
  using size_t = std::size_t;

  using MemoryMap = llvm::IntervalMap<uint64_t, Memory*>;

public:
  virtual MemoryAccessResult write(const MemoryAddress &Addr, const ArrayRef &data) override;
  virtual MemoryAccessResult read (const MemoryAddress &Addr, size_t size) override;

private:
  MemoryMap::Allocator MemoryMapAllocator;
  MemoryMap Map;
}; // class MemoryDispatcher

} // end namespace llr

#endif //LLR_LIB_MEMORY_MEMORYDISPATCHER_H

