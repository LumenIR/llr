#include "LumenIRLLRDecoder.h"

#include "llr/Instruction/LLRInst.h"
#include "llr/Memory/MemoryAddress.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_os_ostream.h"

#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCAsmInfo.h"


#define GET_INSTRINFO_ENUM
#include "LumenIRGenInstrInfo.inc"
#undef GET_INSTRINFO_ENUM

#define DEBUG_TYPE "lumenir-llr-decoder"

using namespace llvm;
using namespace llr;

LumenIRLLRDecoder::LumenIRLLRDecoder() {

  //TODO
  std::string Triple("lumenir");
  std::string error_msg;

  const Target *TheTarget = TargetRegistry::lookupTarget(Triple, error_msg);

  MCRegisterInfo *MRI = TheTarget->createMCRegInfo(Triple);
  MCSubtargetInfo *STI = TheTarget->createMCSubtargetInfo(Triple, "unknown", "");

  MCAsmInfo* MAI = TheTarget->createMCAsmInfo(*MRI, Triple);

  MCContext MCCtx(MAI, MRI, nullptr);

  disasm = TheTarget->createMCDisassembler(*STI, MCCtx);
}


static void print_instruction(LLRContext& Ctx, LLRInst& Inst) {
  Inst.dump();
}



LLRInst LumenIRLLRDecoder::decode(ArrayRef<uint8_t> data, const MemoryAddress &Address) const {

  MCInst MCInstr;

  uint64_t Size = 0;
  MCDisassembler::DecodeStatus status = disasm->getInstruction(MCInstr, Size, data, static_cast<uint64_t>(Address), dbgs(), dbgs());

  assert(status == MCDisassembler::DecodeStatus::Success && "Decoder errror");

  return LLRInst(MCInstr, print_instruction);
}

