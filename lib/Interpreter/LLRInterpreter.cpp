#include "llr/Interpreter/LLRInterpreter.h"
#include "llr/Instruction/LLRInst.h"
#include "llr/Context/LLRContext.h"
#include "llr/Decoder/LLRDecoder.h"
#include "llr/Fetcher/LLRFetcher.h"
#include "llr/Memory/MemoryAccessResult.h"


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


  while(Ctx->isRunning() && CNT++ < 100) {
    MemoryAccessResult data = fetcher->fetchNext(*Ctx);
    dbgs() << "Fetched 0x";
    dbgs().write_hex(data.data[0]);
    dbgs() << " ";
    dbgs().write_hex(data.data[1]);
    dbgs() << " ";
    dbgs().write_hex(data.data[2]);
    dbgs() << " ";
    dbgs().write_hex(data.data[3]);
    dbgs() << " ";
    dbgs() << "\n";

    LLRInst inst = decoder->decode(data.getData(), data.getAddress());

    inst.execute(*Ctx);
  }
}
