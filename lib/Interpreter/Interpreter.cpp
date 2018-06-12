#include "llr/Interpreter/Interpreter.h"
#include "llr/Instruction/LLRInst.h"
#include "llr/Context/Context.h"
#include "llr/Decoder/Decoder.h"
#include "llr/Fetcher/Fetcher.h"
#include "llr/Memory/MemoryAccessResult.h"

using namespace llr;
//using namespace llvm;

Interpeter::Interpeter(Context &context, Fetcher &f, Decoder &d) :
  Ctx(context),
  decoder(d),
  fetcher(f) {

}


void Interpeter::run() {


  while(Ctx.isRunning()) {
    MemoryAccessResult data = fetcher.fetchNext(Ctx);

    LLRInst inst = decoder.decode(data.getData());

    inst.execute(Ctx);
  }
}
