//===- llr/Memory/MemoryAddress.h - Memory address --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_MEMORY_MEMORYADDRESS_H
#define LLR_MEMORY_MEMORYADDRESS_H

#include <cstdint>

namespace llr {


class MemoryAddress {
public:
  MemoryAddress(uint64_t Addr) {
    Address = Addr;
  }

  operator uint64_t() const {
    return Address;
  }

private:
  uint64_t Address;

}; // class MemoryAddress

} // end namespace llr

#endif //LLR_LIB_MEMORY_MEMORYADDRESS_H

