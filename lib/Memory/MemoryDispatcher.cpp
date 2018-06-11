#include "llr/Memory/MemoryDispatcher.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"

using namespace llr;
using namespace llvm;

using MAS = enum MemoryAccessStatus;

MemoryDispatcher::MemoryDispatcher()  :
 Map(MemoryMapAllocator) {
}

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

const MemoryAddress MemoryDispatcher::begin_address() const {
  return MemoryAddress(0);
}

const MemoryAddress MemoryDispatcher::end_address() const {
  return MemoryAddress(0xffffffff);
}

void MemoryDispatcher::registerMemory(Memory* M) {
  Map.insert(M->begin_address(), M->end_address(), M);
}

