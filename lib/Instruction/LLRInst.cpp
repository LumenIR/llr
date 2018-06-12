#include "llr/Instruction/LLRInst.h"
#include "llr/Context/Context.h"

using namespace llr;
using namespace llvm;


LLRInst::LLRInst(MCInst &Instr) :
  MCInstr(Instr) {

}

void LLRInst::execute(Context &Ctx) {
  //TODO
}

