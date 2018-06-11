#include "llr/Memory/SimpleMemory.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Memory/MemoryBlock.h"


#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llr;
using namespace llvm;

using MAS = MemoryAccessStatus;

MemoryAccessResult SimpleMemory::write(const MemoryAddress &Addr, const ArrayRef &data) {

  MemoryAccessResult res = Dispatcher.write(Addr, data);

  if (res.getStatus() == MAS::NotFound) {
    Memory * newM = new MemoryBlock(Addr, {(uint64_t)Addr + data.size()});
    Dispatcher.registerMemory(newM);

    return newM->write(Addr, data);
  } else {

    return res;
  }
}

MemoryAccessResult SimpleMemory::read(const MemoryAddress &Addr, size_t size) {
  return Dispatcher.read(Addr, size);
}

const MemoryAddress SimpleMemory::begin_address() const {
  return Dispatcher.begin_address();
}

const MemoryAddress SimpleMemory::end_address() const {
  return Dispatcher.begin_address();
}
