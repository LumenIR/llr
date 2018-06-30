#include "LumenIRTarget.h"
#include "LumenIRRegisterFile.h"

#include "llr/Memory/SimpleMemory.h"
#include "llr/Context/Context.h"

using namespace llvm;
using namespace llr;





std::unique_ptr<LLRTarget> createLumenIRLLRTarget() {

  SimpleMemoryManager *memory = new SimpleMemoryManager();

  RegisterFile *regFile = new LumenIRRegisterFile();



}
