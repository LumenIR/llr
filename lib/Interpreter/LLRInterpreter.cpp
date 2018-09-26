#include "llr/Interpreter/LLRInterpreter.h"
#include "llr/Instruction/LLRInst.h"
#include "llr/Context/LLRContext.h"
#include "llr/Decoder/LLRDecoder.h"
#include "llr/Fetcher/LLRFetcher.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Registers/LLRRegisterFile.h"
#include "llr/Registers/LLRRegister.h"


#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_os_ostream.h"


using namespace llr;
using namespace llvm;

LLRInterpreter::LLRInterpreter(LLRContext *context, LLRFetcher *f, LLRDecoder *d) :
  Ctx(context),
  fetcher(f),
  decoder(d) {

}

static int CNT = 0;


void LLRInterpreter::run() {


  while(Ctx->isRunning() && CNT++ < 100000) {
    dbgs() << "=S=====================================\n";

    MemoryAccessResult data = fetcher->fetchNext(*Ctx);
/*    dbgs() << "Fetched 0x";
    dbgs().write_hex(data.data[0]);
    dbgs() << " ";
    dbgs().write_hex(data.data[1]);
    dbgs() << " ";
    dbgs().write_hex(data.data[2]);
    dbgs() << " ";
    dbgs().write_hex(data.data[3]);
    dbgs() << " ";
    dbgs() << "\n";
*/
    LLRInst inst = decoder->decode(data.getData(), data.getAddress(), *Ctx);

    inst.execute(*Ctx);

    auto& PC = Ctx->getRegisterFile().getPC();
    if (!Ctx->isBranch()) {
      uint32_t pcValue = *reinterpret_cast<const uint32_t*>(PC.get().getData().data());

      PC.set((uint32_t)(pcValue + inst.getSize()));

      dbgs() << "not a branch\n";
    } else {
      dbgs() << "branch\n";
    }
    Ctx->setBranch(false);
    dbgs() << "=F=====================================\n";

  }
}
