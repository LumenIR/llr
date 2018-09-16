#include "RISCVLLRTarget.h"

#include "RISCVLLRContext.h"
#include "RISCVLLRRegisterFile.h"
#include "RISCVLLRFetcher.h"
#include "RISCVLLRDecoder.h"

#include "llr/Context/LLRContext.h"
#include "llr/Context/LLRContextBase.h"
#include "llr/Interpreter/LLRInterpreter.h"
#include "llr/Memory/PageMemoryManager.h"
#include "llr/Target/LLRTarget.h"
#include "llr/Target/LLRTargetRegistry.h"

using namespace llvm;
using namespace llr;


RISCVLLRTarget::RISCVLLRTarget(LLRContext *ctx, LLRInterpreter *interp) :
  LLRTarget(
      Triple("riscv"),
      ctx,
      interp
  ) {
}


static LLRTarget * TheRISCVTarget;


//TODO rework
LLRTarget * createRISCVLLRTarget() {
  if (TheRISCVTarget != nullptr) {
    return TheRISCVTarget;
  } else {
    Memory *memory = new PageMemoryManager();
    LLRRegisterFile *regFile = new RISCVLLRRegisterFile();

    LLRContext *Ctx = new RISCVLLRContext(memory, regFile, nullptr);
    LLRInterpreter *interp = new LLRInterpreter(Ctx, new RISCVLLRFetcher(), new RISCVLLRDecoder());

    TheRISCVTarget = new RISCVLLRTarget(Ctx, interp);
    return TheRISCVTarget;
  }
}

extern "C" void LLRInitializeRISCVTarget() {
  registry::registerTarget(Triple("riscv"), createRISCVLLRTarget);
}

