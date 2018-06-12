#include "llr/Instruction/LLRInst.h"

using namespace llr;
using namespace llvm;


LLRInst::LLRInst(MCInst &Instr) :
  MCInstr(Instr) {

}

void LLRInst::execute(Context &Ctx) {
  //TODO
}

