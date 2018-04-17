#include "MemoryDispatcher.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"

using namespace llr;
using namespace llvm;

using MAS = enum MemoryAccessStatus;

MemoryAccessResult MemoryDispatcher::write(const MemoryAddress &Addr, const ArrayRef &data) {

  Memory *Mem_ptr = Map.lookup(Addr, nullptr);

  if (Mem_ptr == nullptr) {
    return MemoryAccessResult(MAS::NotFound);
  } else {
    return Mem_ptr->write(Addr, data);
  }
}

MemoryAccessResult MemoryDispatcher::read(const MemoryAddress &Addr, size_t size) {

  Memory *Mem_ptr = Map.lookup(Addr, nullptr);

  if (Mem_ptr == nullptr) {
    return MemoryAccessResult(MAS::NotFound);
  } else {
    return Mem_ptr->read(Addr, size);
  }
}

