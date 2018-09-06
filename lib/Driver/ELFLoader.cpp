#include "llr/Driver/ELFLoader.h"

#include "llr/Context/LLRContext.h"
#include "llr/Memory/Memory.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Memory/MemoryAccessResult.h"

#include "llvm/ADT/StringRef.h"

#include "elfio/elfio_dump.hpp"
#include "elfio/elfio.hpp"


using namespace llr;
using namespace llvm;

void ELFLoader::loadFile(StringRef file, LLRContext &Ctx) const {
  ELFIO::elfio reader;

  Memory &Mem = Ctx.getMemory();

  reader.load(file);

  for(ELFIO::segment *segment : reader.segments) {
    const uint8_t *data = reinterpret_cast<const uint8_t *>(segment->get_data());
    MemoryAddress Addr = segment->get_virtual_address();
    size_t Size = segment->get_file_size();

    Mem.write(Addr, {data, Size});
  }



}


