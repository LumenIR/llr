#include "LumenIRLLRFetcher.h"

#include "LumenIRRegisterFile.h"

#include "llr/Context/LLRContext.h"
#include "llr/Registers/RegisterAccessResult.h"
#include "llr/Registers/RegisterFile.h"
#include "llr/Registers/LLRRegister.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/Memory.h"

using namespace llvm;
using namespace llr;

MemoryAccessResult LumenIRLLRFetcher::fetchNext(const LLRContext& Ctx) const {
   RegisterFile &Regs = Ctx.getRegisterFile();
   LLRRegister &PC = Regs.getRegisterById(LumenIR::PC);


   ArrayRef<uint8_t> pcData = PC.get().getData();

   uint64_t pcValue = *reinterpret_cast<const uint64_t*>(pcData.data());

   Memory &Mem = Ctx.getMemory();

   return Mem.read({pcValue}, 12);
}
