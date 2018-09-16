#include "RISCVLLRFetcher.h"

#include "RISCVLLRRegisterFile.h"

#include "llr/Context/LLRContext.h"
#include "llr/Registers/RegisterAccessResult.h"
#include "llr/Registers/LLRRegisterFile.h"
#include "llr/Registers/LLRRegister.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/Memory.h"

using namespace llvm;
using namespace llr;

MemoryAccessResult RISCVLLRFetcher::fetchNext(const LLRContext& Ctx) const {
   LLRRegisterFile &Regs = Ctx.getRegisterFile();
   LLRRegister &PC = Regs.getRegisterById(0);


   ArrayRef<uint8_t> pcData = PC.get().getData();

   uint64_t pcValue = *reinterpret_cast<const uint64_t*>(pcData.data());

   Memory &Mem = Ctx.getMemory();

   return Mem.read({pcValue}, 12);
}
