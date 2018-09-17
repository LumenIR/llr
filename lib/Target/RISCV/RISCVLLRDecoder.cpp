#include "RISCVLLRDecoder.h"

#include "llr/Instruction/LLRInst.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Context/LLRContext.h"
#include "llr/Registers/LLRRegisterFile.h"
#include "llr/Registers/LLRRegister.h"

#include "llvm/ADT/Triple.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_os_ostream.h"

#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/MCTargetOptionsCommandFlags.inc"

#define GET_INSTRINFO_ENUM
#include "RISCVGenInstrInfo.inc"
#undef GET_INSTRINFO_ENUM

#define DEBUG_TYPE "llr-riscv-decoder"

using namespace llvm;
using namespace llr;

RISCVLLRDecoder::RISCVLLRDecoder() {

  //TODO
  std::string TripleName = Triple::normalize("riscv32-unknown-elf");
  llvm::Triple TheTriple(TripleName);

  std::string error_msg;

  const Target *TheTarget = TargetRegistry::lookupTarget(TripleName, error_msg);
  assert(TheTarget != nullptr && "Unable to create RISCV32 llvm Target");

  MRI.reset(TheTarget->createMCRegInfo(TripleName));
  assert(MRI != nullptr && "Unable to create RISCV32 llvm MCRegisterInfo");

  STI.reset(TheTarget->createMCSubtargetInfo(TripleName, "", ""));
  assert(STI != nullptr && "Unable to create RISCV32 llvm MCSubtargetInfo");

  MAI.reset(TheTarget->createMCAsmInfo(*MRI, TripleName));
  assert(MAI != nullptr && "Unable to create RISCV32 llvm MCAsmInfo");

  MCII.reset(TheTarget->createMCInstrInfo());
  assert(MCII != nullptr && "Unable to create RISCV32 llvm MCInstrInfo");


  MCObjectFileInfo MOFI;
  MCContext MCCtx(MAI.get(), MRI.get(), &MOFI);
  MOFI.InitMCObjectFileInfo(TheTriple, false, MCCtx);

  //TODO get it from LLRContext
//  MCCtx.setMainFileName("a.out");
//  MCCtx.setUseNamesOnTempLabels(false);

  disasm.reset(TheTarget->createMCDisassembler(*STI, MCCtx));
  assert(disasm != nullptr && "Unable to create RISCV32 llvm dissasembler");


  IP.reset(TheTarget->createMCInstPrinter(TheTriple, 0, *MAI, *MCII, *MRI));
  assert(IP != nullptr && "Unable to create RISCV32 llvm MCInstPrinter");

//  std::unique_ptr<MCCodeEmitter> CE(TheTarget->createMCCodeEmitter(*MCII, *MRI, MCCtx));

//  MCTargetOptions MCOptions = InitMCTargetOptionsFromFlags();

//  std::unique_ptr<MCAsmBackend> MAB(TheTarget->createMCAsmBackend(*STI, *MRI, MCOptions));

//  auto FOut = llvm::make_unique<formatted_raw_ostream>(dbgs());

//  Streamer.reset(
//        TheTarget->createAsmStreamer(MCCtx, std::move(FOut), /*asmverbose*/ true, /*useDwarfDir*/ true, IP, std::move(CE), std::move(MAB), true)
//        );
//  Streamer->InitSections(false);
}


static void print_instruction(LLRContext& Ctx, LLRInst& Inst) {
//  Inst.dump();
}

static void exec_AUIPC(LLRContext& Ctx, LLRInst& Inst) {

  uint32_t ImmVal = Inst.getMCInst().getOperand(1).getImm();
  unsigned regId = Inst.getMCInst().getOperand(0).getReg();

  uint32_t PCVal = *reinterpret_cast<const uint32_t*>(Ctx.getRegisterFile().getPC().get().getData().data());

  Ctx.getRegisterFile().getRegisterById(regId).set(PCVal + ImmVal);
}




LLRInst RISCVLLRDecoder::decode(ArrayRef<uint8_t> data, const MemoryAddress &Address) const {
  dbgs() << "Trying to decode 0x";
  dbgs().write_hex(data[0]);
  dbgs() << " ";
  dbgs().write_hex(data[1]);
  dbgs() << " ";
  dbgs().write_hex(data[2]);
  dbgs() << " ";
  dbgs().write_hex(data[3]);
  dbgs() << " ";
  dbgs() << "\n";


  MCInst MCInstr;

  uint64_t Size = 0;
  MCDisassembler::DecodeStatus status = disasm->getInstruction(MCInstr, Size, data, static_cast<uint64_t>(Address), dbgs(), dbgs());

//  assert(status == MCDisassembler::DecodeStatus::Success && "Decoder errror");

  if (status == MCDisassembler::DecodeStatus::Success) {
    MCInstr.dump_pretty(dbgs(), IP.get());
    dbgs() << "Disasm: ";
//    Streamer->EmitInstruction(MCInstr, *STI);
  }


  void (*execution_func)(LLRContext &, LLRInst &) = print_instruction;
  switch (MCInstr.getOpcode()) {
  case RISCV::AUIPC: execution_func = exec_AUIPC; break;

  }


  return LLRInst(MCInstr, execution_func);
}

