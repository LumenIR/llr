//===- llr/Memory/PageMemoryManager.h -------------------*- C++ -*---------===//
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

#ifndef LLR_MEMORY_PAGEMEMORYMANAGER_H
#define LLR_MEMORY_PAGEMEMORYMANAGER_H

#include "llr/Memory/Memory.h"
#include "llr/Memory/MemoryAddress.h"

#include "llvm/ADT/ArrayRef.h"

#include <memory>
#include <unordered_map>
#include <cstdint>

namespace llr {

class MemoryAccessResult;
struct MemoryPage {
  bool isValid = false;
  std::vector<uint8_t> data;
//  llvm::ArrayRef<uint8_t> data;
};

using MemoryPage_uptr = std::unique_ptr<MemoryPage>;

class PageMemoryManager : public Memory {
  using size_t = std::size_t;

public:
  PageMemoryManager();
//  PageMemoryManager(size_t PageSize, size_t PageNumber);

  virtual MemoryAccessResult write(const MemoryAddress &Addr, const llvm::ArrayRef<uint8_t> &data) override;
  virtual MemoryAccessResult read (const MemoryAddress &Addr, size_t size) override;

  virtual const MemoryAddress begin_address() const override;
  virtual const MemoryAddress end_address() const override;

private:
  MemoryAddress begin_addr;
  MemoryAddress end_addr;

  const size_t PageSize;

  std::unordered_map<uint64_t, MemoryPage_uptr> pages;

}; // class PageMemoryManager



} // end namespace llr

#endif //LLR_MEMORY_PAGEMEMORYMANAGER_H

