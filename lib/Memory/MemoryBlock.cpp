#include "llr/Memory/MemoryBlock.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"

#include <algorithm>
#include <cassert>

using namespace llr;
using namespace llvm;

using MAS = enum MemoryAccessStatus;

MemoryBlock::MemoryBlock(const MemoryAddress b, const MemoryAddress e) :
  begin_addr(b),
  end_addr(e) {
  assert(b < e && "Trying to create memory block with begin address >= end address");

  data.resize((uint64_t)e - (uint64_t)b);
}


MemoryAccessResult MemoryBlock::write(const MemoryAddress &Addr, const ArrayRef &d) {
  assert(Addr <= begin_addr || Addr > end_addr && "");

  std::copy(d.begin(), d.end(), data.begin());

  return {MAS::WriteOK};
}

MemoryAccessResult MemoryBlock::read(const MemoryAddress &Addr, size_t size) {
  assert(Addr <= begin_addr || Addr > end_addr && "");

  return {MAS::ReadOK, ArrayRef(data.data() + Addr - begin_addr, size)};
}

const MemoryAddress MemoryBlock::begin_address() const {
  return begin_addr;
}

const MemoryAddress MemoryBlock::end_address() const {
  return end_addr;
}
