//===- llr/Memory/SimpleMemory.h - ess interface --------*- C++ -*---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  Allocate memory on access
//
//===----------------------------------------------------------------------===//

#ifndef LLR_MEMORY_SIMPLEMEMORY_H
#define LLR_MEMORY_SIMPLEMEMORY_H

#include "llr/Memory/Memory.h"
#include "llr/Memory/MemoryDispatcher.h"

#include "llvm/ADT/ArrayRef.h"

#include <cstdint>

//namespace llvm {
//class ArrayRef;
//}

namespace llr {

class MemoryAccessResult;
class MemoryAddress;

class SimpleMemoryManager : public Memory {
  using ArrayRef = llvm::ArrayRef<uint8_t>;
  using size_t = std::size_t;

public:
  virtual MemoryAccessResult write(const MemoryAddress &Addr, const ArrayRef &data) override;
  virtual MemoryAccessResult read (const MemoryAddress &Addr, size_t size) override;

  virtual const MemoryAddress begin_address() const override;
  virtual const MemoryAddress end_address() const override;

private:
  MemoryDispatcher Dispatcher;

}; // class SimpleMemory


} // end namespace llr

#endif //LLR_MEMORY_SIMPLEMEMORY_H

