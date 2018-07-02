#include "llr/Instruction/LLRInst.h"
#include "llr/Context/LLRContext.h"

#include "llvm/MC/MCInst.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_os_ostream.h"

using namespace llr;
using namespace llvm;


LLRInst::LLRInst(MCInst Instr, void(*func)(LLRContext&, LLRInst&)) :
  MCInstr(Instr),
  execution_func(func) {

}

void LLRInst::execute(LLRContext &Ctx) {
  execution_func(Ctx, *this);
}


void LLRInst::print(raw_ostream &OS) const {
  MCInstr.print(OS);
}

void LLRInst::dump() const {
  print(dbgs());
  dbgs() << "\n";
}
