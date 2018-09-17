#include "RISCVLLRFetcher.h"

#include "RISCVLLRRegisterFile.h"

#include "llr/Context/LLRContext.h"
#include "llr/Registers/RegisterAccessResult.h"
#include "llr/Registers/LLRRegisterFile.h"
#include "llr/Registers/LLRRegister.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/Memory.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_os_ostream.h"

using namespace llvm;
using namespace llr;

MemoryAccessResult RISCVLLRFetcher::fetchNext(const LLRContext& Ctx) const {
   LLRRegisterFile &Regs = Ctx.getRegisterFile();
   LLRRegister &PC = Regs.getPC();


   ArrayRef<uint8_t> pcData = PC.get().getData();

   uint32_t pcValue = *reinterpret_cast<const uint32_t*>(pcData.data());

   dbgs() << "Fetching instruction from address: 0x";
   dbgs().write_hex(pcValue);
   dbgs() << "\n";

   PC.set(pcValue + 4);

   Memory &Mem = Ctx.getMemory();

   MemoryAccessResult res = Mem.read({pcValue}, 4);
   dbgs() << "Fetched: ";
   res.dump();

   return res;
}
