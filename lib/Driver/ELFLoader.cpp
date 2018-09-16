#include "llr/Driver/ELFLoader.h"

#include "llr/Context/LLRContext.h"
#include "llr/Memory/Memory.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Memory/MemoryAccessResult.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#include "elfio/elfio_dump.hpp"
#include "elfio/elfio.hpp"

#define DEBUG_TYPE "llr-elfloader"

using namespace llr;
using namespace llvm;

void ELFLoader::loadFile(StringRef file, LLRContext &Ctx) const {
  dbgs() << "Loading elf file to memory: " << file << "\n";

  ELFIO::elfio reader;

  Memory &Mem = Ctx.getMemory();

  if (!reader.load(file)) {
    report_fatal_error(llvm::Twine("Failed to load elf file: ") + file);
    return;
  }

  for (ELFIO::segment *segment : reader.segments) {

    const uint8_t *data = reinterpret_cast<const uint8_t *>(segment->get_data());
    MemoryAddress Addr = segment->get_virtual_address();
    size_t Size = segment->get_file_size();

    LLVM_DEBUG(
        dbgs() << "Found segment virtual address: 0x";
        dbgs().write_hex(Addr);
        dbgs() << ", size: " << Size;
        dbgs() << "\n";
    );

    if (Size == 0) {
      continue;
    }
    Mem.write(Addr, {data, Size});
  }
}


