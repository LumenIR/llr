//===- llr/Memory/MemoryBlock.h -------------------------*- C++ -*---------===//
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

#ifndef LLR_MEMORY_MEMORYBLOCK_H
#define LLR_MEMORY_MEMORYBLOCK_H

#include "llr/Memory/Memory.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Memory/MemoryDispatcher.h"

#include "llvm/ADT/ArrayRef.h"

#include <vector>
#include <cstdint>

namespace llr {

class MemoryAccessResult;

class MemoryBlock : public Memory {
  using size_t = std::size_t;

public:
  MemoryBlock() = delete;
  MemoryBlock(const MemoryAddress b, const MemoryAddress e);

  virtual MemoryAccessResult write(const MemoryAddress &Addr, const llvm::ArrayRef<uint8_t> &data) override;
  virtual MemoryAccessResult read (const MemoryAddress &Addr, size_t size) override;

  virtual const MemoryAddress begin_address() const override;
  virtual const MemoryAddress end_address() const override;

private:
  MemoryAddress begin_addr;
  MemoryAddress end_addr;

  std::vector<uint8_t> data;

}; // class SimpleMemory

} // end namespace llr

#endif //LLR_MEMORY_MEMORYBLOCK_H

