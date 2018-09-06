#include "LumenIRTarget.h"

#include "LumenIRContext.h"
#include "LumenIRRegisterFile.h"
#include "LumenIRLLRFetcher.h"
#include "LumenIRLLRDecoder.h"

#include "llr/Context/LLRContext.h"
#include "llr/Context/LLRContextBase.h"
#include "llr/Interpreter/Interpreter.h"
#include "llr/Memory/PageMemoryManager.h"
#include "llr/Target/LLRTarget.h"
#include "llr/Target/LLRTargetRegistry.h"

using namespace llvm;
using namespace llr;


LumenIRLLRTarget::LumenIRLLRTarget(LLRContext *ctx, Interpreter *interp) :
  LLRTarget(
      Triple("lumenir"),
      ctx,
      interp
  ) {
}


static LLRTarget * TheLumenIRTarget;


//TODO rework
LLRTarget * createLumenIRLLRTarget() {
  if (TheLumenIRTarget != nullptr) {
    return TheLumenIRTarget;
  } else {
    Memory *memory = new PageMemoryManager();
    RegisterFile *regFile = new LumenIRRegisterFile();

    LLRContext *Ctx = new LumenIRLLRContext(memory, regFile, nullptr);
    Interpreter *interp = new Interpreter(Ctx, new LumenIRLLRFetcher(), new LumenIRLLRDecoder());

    TheLumenIRTarget = new LumenIRLLRTarget(Ctx, interp);
    return TheLumenIRTarget;
  }
}

extern "C" void LLRInitializeLumenIRTarget() {
  registry::registerTarget(Triple("lumenir"), createLumenIRLLRTarget);
}


