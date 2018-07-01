#include "llr/Interpreter/Interpreter.h"
#include "llr/Instruction/LLRInst.h"
#include "llr/Context/LLRContext.h"
#include "llr/Decoder/LLRDecoder.h"
#include "llr/Fetcher/LLRFetcher.h"
#include "llr/Memory/MemoryAccessResult.h"

using namespace llr;
//using namespace llvm;

Interpreter::Interpreter(LLRContext &context, LLRFetcher &f, LLRDecoder &d) :
  Ctx(context),
  fetcher(f),
  decoder(d) {

}


void Interpreter::run() {


  while(Ctx.isRunning()) {
    MemoryAccessResult data = fetcher.fetchNext(Ctx);

    LLRInst inst = decoder.decode(data.getData());

    inst.execute(Ctx);
  }
}
