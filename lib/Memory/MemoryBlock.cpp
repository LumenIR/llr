#include "llr/Memory/MemoryBlock.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"

#include <algorithm>
#include <cassert>
#include <cstdint>

using namespace llr;
using namespace llvm;

using MAS = enum MemoryAccessStatus;

MemoryBlock::MemoryBlock(const MemoryAddress b, const MemoryAddress e) :
  begin_addr(b),
  end_addr(e) {
  assert((uint64_t)b < (uint64_t)e && "Trying to create memory block with begin address >= end address");

  data.resize((uint64_t)e - (uint64_t)b);
}



MemoryAccessResult MemoryBlock::write(const MemoryAddress &Addr, const ArrayRef<uint8_t> &d) {
  assert(   (uint64_t)Addr            >= (uint64_t)begin_addr
         && (uint64_t)Addr + d.size() <= (uint64_t)end_addr
         && "Writing to block memory out of bounds");

  uint64_t LocalAddress = (uint64_t)Addr - (uint64_t)begin_addr;

  std::copy(d.begin(), d.end(), data.begin() + LocalAddress);

  return {MAS::WriteOK, d, Addr};
}

MemoryAccessResult MemoryBlock::read(const MemoryAddress &Addr, size_t size) {
  assert((   (uint64_t)Addr        >= (uint64_t)begin_addr)
         && ((uint64_t)Addr + size <= (uint64_t)end_addr)
         && "Reading from block memory out of bounds");

  uint64_t LocalAddress = (uint64_t)Addr - (uint64_t)begin_addr;

  return {MAS::ReadOK, ArrayRef<uint8_t>(data.data() + LocalAddress, size), Addr};
}

const MemoryAddress MemoryBlock::begin_address() const {
  return begin_addr;
}

const MemoryAddress MemoryBlock::end_address() const {
  return end_addr;
}
