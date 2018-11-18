#include "llr/Instruction/LLRInst.h"
#include "llr/Context/LLRContext.h"
#include "llr/Registers/LLRRegisterFile.h"
#include "llr/Registers/LLRRegister.h"


#include "llvm/MC/MCInst.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_os_ostream.h"

using namespace llr;
using namespace llvm;


LLRInst::LLRInst(MCInst Instr, size_t S, LLRContext &Ctx, llr_execution_func func) :
  MCInstr(Instr),
  Size(S),
  execution_func(func) {

  for(unsigned i = 0; i < Instr.getNumOperands(); ++i) {
    MCOperand mc_op  = Instr.getOperand(i);
    if (mc_op.isImm()) {
      operands.push_back(LLROperand::createImmOperand(mc_op.getImm()));
    } else if (mc_op.isReg()) {
      operands.push_back(LLROperand::createRegisterOperand(&Ctx.getRegisterFile().getRegisterById(mc_op.getReg())));
    }
  }
}

void LLRInst::execute(LLRContext &Ctx) {
  execution_func(Ctx, *this);
}


void LLRInst::print(raw_ostream &OS) const {
//  MCInstr.print(OS);
//  OS << " ";
  for(unsigned i = 0; i < getNumOperands(); ++i) {
    LLROperand Op = getOperand(i);
    if (Op.isImm()) {
      OS << "Imm:" << Op.getImm();
    } else if (Op.isRegister()) {
      OS << "RegVal:" << Op.getRegister().get().asInt32();
    }
    OS << " ";
  }
}

void LLRInst::dump() const {
  print(dbgs());
  dbgs() << "\n";
}
