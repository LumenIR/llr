#include "RISCVLLRExecutionFunctions.h"

//TMP
#include "RISCVLLRRegisterFile.h"

#include "llr/Instruction/LLRInst.h"
#include "llr/Memory/MemoryAddress.h"
#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/Memory.h"

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


using namespace llvm;
using namespace llr;

#define GET_INSTRINFO_ENUM
#include "RISCVGenInstrInfo.inc"
#undef GET_INSTRINFO_ENUM


static void print_instruction(LLRContext& Ctx, LLRInst& Inst) {
//  Inst.dump();
}

static void exec_AUIPC(LLRContext& Ctx, LLRInst& Inst) {

  int32_t ImmVal = Inst.getOperand(1).getImm();

  uint32_t PCVal = Ctx.getRegisterFile().getPC().get().asUint32();

  uint32_t newPCVal = (PCVal + (ImmVal << 12));

  Inst.getOperand(0).getRegister().set(
          newPCVal
  );

  dbgs() << "NewVal: " << newPCVal << " (0x";
  dbgs().write_hex(newPCVal);
  dbgs() << ")\n";
}

static void exec_LUI(LLRContext& Ctx, LLRInst& Inst) {
    unsigned Opc = Inst.getOpcode();
    assert(Opc == RISCV::LUI);

    uint32_t OldVal = Inst.getOperand(0).getRegister().get().asUint32();
    uint32_t Imm    = Inst.getOperand(1).getImm();

    //| 31 -12 |   11-0
    //|xxxxxxxx|000000000000

    //TODO  and sign-extends bit 17 into all higher bits of the destinatio
    uint32_t NewVal = (Imm << 12) ;

    Inst.getOperand(0).getRegister().set(
            NewVal
    );

    dbgs() << "New val: 0x";
    dbgs().write_hex(NewVal);
    dbgs() << "\n";
}

static void exec_ADDI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::ADDI
         || Opc == RISCV::C_ADDI);


  uint32_t rhs1 = Inst.getOperand(1).getRegister().get().asUint32();
  int32_t rhs2_imm = Inst.getMCInst().getOperand(2).getImm();


  uint32_t new_val = rhs1 + (uint32_t)rhs2_imm;

  Inst.getOperand(0).getRegister().set(
          new_val
  );

  dbgs() << "New val: 0x";
  dbgs().write_hex(new_val);
  dbgs() << " = " << rhs1 << " + " << rhs2_imm;

  dbgs() << "\n";
}


static void exec_ADDI4SPN(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::C_ADDI4SPN);


  LLRRegister& DstReg = Inst.getOperand(0).getRegister();

  uint32_t rhs1 = Inst.getOperand(1).getRegister().get().asUint32();
  int32_t rhs2_imm = 4 * Inst.getOperand(2).getImm();

  uint32_t new_val = rhs1 + rhs2_imm;

  DstReg.set(new_val);


  dbgs() << "New val: 0x";
  dbgs().write_hex(new_val);
  dbgs() << " = " << rhs1 << " + " << rhs2_imm;

  dbgs() << "\n";
}

static void exec_C_SUB(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::C_SUB
         || Opc == RISCV::SUB);


  uint32_t rhs1 = Inst.getOperand(1).getRegister().get().asUint32();
  uint32_t rhs2 = Inst.getOperand(2).getRegister().get().asUint32();

  uint32_t new_val = static_cast<uint32_t>(rhs1 - rhs2);

  Inst.getOperand(0).getRegister().set(new_val);

  dbgs() << "New val: " << new_val << "(0x";
  dbgs().write_hex(new_val);
  dbgs() << ") = " << rhs1 << " - " << rhs2;
  dbgs() << "\n";
}

static void exec_DIV(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Opc == RISCV::DIV);


  uint32_t rhs1 = Inst.getOperand(1).getRegister().get().asUint32();
  uint32_t rhs2 = Inst.getOperand(2).getRegister().get().asUint32();

  uint32_t new_val = static_cast<uint32_t>(rhs1 / rhs2);

  Inst.getOperand(0).getRegister().set(new_val);

  dbgs() << "New val: 0x";
  dbgs().write_hex(new_val);
  dbgs() << "\n";
}

static void exec_C_LI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Inst.getMCInst().getOpcode() == RISCV::C_LI);

  Inst.getOperand(0).getRegister().set(
        (uint32_t)Inst.getOperand(1).getImm()
  );

  dbgs() << "New val: 0x";
  dbgs().write_hex(Inst.getOperand(1).getImm());
  dbgs() << "\n";
}

static void exec_C_LUI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Opc == RISCV::C_LUI);

  uint32_t OldVal = Inst.getOperand(0).getRegister().get().asUint32();
  uint32_t Imm    = Inst.getOperand(1).getImm();

  //|31-18    | 17-12|   11-0
  //|ss...ssss|sxxxxx|000000000000

  //TODO  and sign-extends bit 17 into all higher bits of the destinatio
  assert(!(Imm & (1 << 12)) && "Signe extension in LUI not implemented");
  uint32_t NewVal = (OldVal & (Imm << 12)) ;

  Inst.getOperand(0).getRegister().set(
        NewVal
  );

  dbgs() << "New val: 0x";
  dbgs().write_hex(NewVal);
  dbgs() << "\n";
}



static void exec_JR(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(    Opc == RISCV::C_JR
          || Opc == RISCV::C_JALR);

  auto &PC = Ctx.getRegisterFile().getPC();
  uint32_t PCVal = PC.get().asUint32();

  PC.set(
        Inst.getOperand(0).getRegister().get().getData()
  );
  Ctx.setBranch(true);

  if (Opc == RISCV::C_JALR) {
    auto &LinkReg = Ctx.getRegisterFile().getRegisterById(RISCV::X1);

    LinkReg.set((uint32_t)(PCVal + Inst.getSize()));
  }

  dbgs() << "Jump to 0x";
  dbgs().write_hex(Inst.getOperand(0).getRegister().get().asUint32());
  dbgs() << "\n";
}

static void exec_J(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert( Opc == RISCV::C_J);

  auto &PC = Ctx.getRegisterFile().getPC();
  auto PCVal = Ctx.getRegisterFile().getPC().get().asUint32();

  int32_t Offset = Inst.getOperand(0).getImm();

  PC.set(
        (uint32_t)(PCVal + Offset)
  );
  Ctx.setBranch(true);

  dbgs() << "Jump to 0x";
  dbgs().write_hex(PCVal + Offset);
  dbgs() << "\n";
}

static void exec_C_JAL(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::C_JAL);

  auto &PC = Ctx.getRegisterFile().getPC();
  uint32_t PCVal = PC.get().asUint32();

  int32_t immOffset = Inst.getOperand(0).getImm();

  uint32_t newPC = PCVal + immOffset;
  PC.set(newPC);
  Ctx.setBranch(true);

  unsigned LinkRegId = RISCV::X1;
  auto &LinkReg = Ctx.getRegisterFile().getRegisterById(LinkRegId);
  LinkReg.set((uint32_t)(PCVal + Inst.getSize()));


  dbgs() << "new PC: 0x";
  dbgs().write_hex(newPC);
  dbgs() << " =  old PC: " << PCVal << " + ImmOffset: " << immOffset << "\n";
}


static void exec_JAL(LLRContext& Ctx, LLRInst& Inst) {
    unsigned Opc = Inst.getOpcode();
    assert(   Opc == RISCV::JAL);

    auto &PC = Ctx.getRegisterFile().getPC();
    uint32_t PCVal = PC.get().asUint32();

    int32_t immOffset = Inst.getOperand(1).getImm();

    uint32_t newPC = PCVal + immOffset;
    PC.set(newPC);
    Ctx.setBranch(true);

    unsigned LinkRegId = Inst.getMCInst().getOperand(0).getReg();
    auto &LinkReg = Ctx.getRegisterFile().getRegisterById(LinkRegId);
    LinkReg.set((uint32_t)(PCVal + Inst.getSize()));


    dbgs() << "new PC: 0x";
    dbgs().write_hex(newPC);
    dbgs() << " =  old PC: " << PCVal << " + ImmOffset: " << immOffset << "\n";
}

static void exec_JALR(LLRContext& Ctx, LLRInst& Inst) {
    unsigned Opc = Inst.getOpcode();
    assert(   Opc == RISCV::JALR);

    auto &PC = Ctx.getRegisterFile().getPC();
    uint32_t PCVal = PC.get().asUint32();

    uint32_t regOffset = Inst.getOperand(1).getRegister().get().asUint32();
    int32_t immOffset = Inst.getOperand(2).getImm();

    uint32_t newPC = (regOffset + immOffset) & 0xFFFFFFFE;
    PC.set(newPC);
    Ctx.setBranch(true);

    auto &LinkReg = Inst.getOperand(0).getRegister();
    LinkReg.set((uint32_t)(PCVal + Inst.getSize()));


    dbgs() << "new PC: 0x";
    dbgs().write_hex(newPC);
    dbgs() << " =  old PC: " << PCVal << " + ImmOffset: " << immOffset << "\n";
}

static void exec_SLT(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::SLT
            || Opc == RISCV::SLTU
            || Opc == RISCV::SLTI
            || Opc == RISCV::SLTIU

  );


  auto &PC = Ctx.getRegisterFile().getPC();

  uint32_t PCVal = PC.get().asUint32();

  uint32_t RHS1_U = Inst.getOperand(1).getRegister().get().asUint32();
  int32_t RHS1_I = Inst.getOperand(1).getRegister().get().asInt32();


  uint32_t RHS2_U;
  int32_t RHS2_I;

  switch (Opc) {
    default: llvm_unreachable("Not implemented");

    case RISCV::SLT:
    case RISCV::SLTU:
      RHS2_I = Inst.getOperand(2).getRegister().get().asInt32();
      RHS2_U = Inst.getOperand(2).getRegister().get().asUint32();
      break;

    case RISCV::SLTI:
    case RISCV::SLTIU:
      RHS2_I = Inst.getOperand(2).getImm();
      RHS2_U = Inst.getOperand(2).getImm();
      break;
  }


  dbgs() << "rhs1: 0x";
  dbgs().write_hex(RHS1_U);
  dbgs() << " rhs2: 0x";
  dbgs().write_hex(RHS2_U);
  dbgs() << "\n";

  bool taken = false;
  switch (Opc) {
    default: llvm_unreachable("Not implemented");
    case RISCV::SLT:
    case RISCV::SLTI:
      if (RHS1_I < RHS2_I) {
        taken = true;

        dbgs() << RHS1_I <<  " < " << RHS2_I << "\n";
      } else {
        dbgs() << RHS1_I <<  " >= " << RHS2_I << "\n";
      }
      break;
    case RISCV::SLTU:
    case RISCV::SLTIU:
      if (RHS1_U < RHS2_U) {
          taken = true;

          dbgs() << RHS1_U <<  " < " << RHS2_U << "\n";
      } else {
          dbgs() << RHS1_U <<  " >= " << RHS2_U << "\n";
      }
      break;
  }

  uint32_t NewVal;
  if (taken) {
    NewVal = 1;
  } else {
    NewVal = 0;
  }
  Inst.getOperand(0).getRegister().set(NewVal);

  dbgs() << "NewVal: " << NewVal << "\n";
}

static void exec_BG(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::BGEU
         || Opc == RISCV::BGE
         || Opc == RISCV::BLTU
         || Opc == RISCV::BLT
         || Opc == RISCV::BEQ
         || Opc == RISCV::BNE
            );


  auto &PC = Ctx.getRegisterFile().getPC();

  uint32_t PCVal = *reinterpret_cast<const uint32_t*>(PC.get().getData().data());

  bool taken = false;

  uint32_t RHS1_U = Inst.getOperand(0).getRegister().get().asUint32();
  uint32_t RHS2_U = Inst.getOperand(1).getRegister().get().asUint32();

  int32_t RHS1_I = Inst.getOperand(0).getRegister().get().asInt32();
  int32_t RHS2_I = Inst.getOperand(1).getRegister().get().asInt32();


  dbgs() << "rhs1: 0x";
  dbgs().write_hex(RHS1_U);
  dbgs() << " rhs2: 0x";
  dbgs().write_hex(RHS2_U);
  dbgs() << "\n";

  switch (Opc) {
  default: llvm_unreachable("Not implemented");
  case RISCV::BGE: {
    if (RHS1_I >= RHS2_I) {
      taken = true;
    }
    break;
  }
  case RISCV::BGEU: {
    if (RHS1_U >= RHS2_U) {
      taken = true;
    }
    break;
  }
  case RISCV::BLTU: {
    if (RHS1_U < RHS2_U) {
      taken = true;
    }
    break;
  }
  case RISCV::BLT: {
    if (RHS1_I < RHS2_I) {
      taken = true;
    }
    break;
  }
  case RISCV::BEQ: {
    if (RHS1_I == RHS2_I) {
      taken = true;
    }
    break;
  }
  case RISCV::BNE: {
    if (RHS1_I != RHS2_I) {
      taken = true;
    }
    break;
  }
  }


  if (taken) {
    PC.set((uint32_t)((int32_t)PCVal + (int32_t)Inst.getOperand(2).getImm()));
    Ctx.setBranch(true);
  } else {
    Ctx.setBranch(false);
  }

}

static void exec_C_BEQZ(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Opc == RISCV::C_BEQZ
         || Opc == RISCV::C_BNEZ);


  auto &PC = Ctx.getRegisterFile().getPC();

  uint32_t PCVal = *reinterpret_cast<const uint32_t*>(PC.get().getData().data());

  bool taken = false;

  uint32_t RHS1 = Inst.getOperand(0).getRegister().get().asUint32();

  if (Opc == RISCV::C_BEQZ) {
    if (RHS1 == 0) {
      taken = true;
    }
  } else if (Opc == RISCV::C_BNEZ) {
    if (RHS1 != 0) {
      taken = true;
    }
  }

  if (taken) {
    Ctx.setBranch(true);
    PC.set((uint32_t)((int32_t)PCVal + (int32_t)Inst.getOperand(1).getImm()));
  } else {
    Ctx.setBranch(false);
  }

}

static void exec_C_MV(LLRContext& Ctx, LLRInst& Inst) {
  assert(Inst.getMCInst().getOpcode() == RISCV::C_MV);

  Inst.getOperand(0).getRegister().set(
        Inst.getOperand(1).getRegister().get().getData()
  );

}

static void exec_ANDI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::ANDI
         || Opc == RISCV::C_ANDI);

  Inst.getOperand(0).getRegister().set(
        Inst.getOperand(1).getRegister().get().asUint32()
        & (uint32_t)Inst.getOperand(2).getImm()
  );
}

static void exec_AND(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::AND);

  Inst.getOperand(0).getRegister().set(
          Inst.getOperand(1).getRegister().get().asUint32()
          & (uint32_t)Inst.getOperand(2).getRegister().get().asUint32()
  );
}

static void exec_XOR(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::XOR);

  Inst.getOperand(0).getRegister().set(
          Inst.getOperand(1).getRegister().get().asUint32()
          ^ (uint32_t)Inst.getOperand(2).getRegister().get().asUint32()
  );
}

static void exec_XORI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Opc == RISCV::XORI);

  Inst.getOperand(0).getRegister().set(
          Inst.getOperand(1).getRegister().get().asUint32()
          ^ (uint32_t)Inst.getOperand(2).getImm()
  );
}

static void exec_OR(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::OR
         || Opc == RISCV::C_OR);

  Inst.getOperand(0).getRegister().set(
          Inst.getOperand(1).getRegister().get().asUint32()
        | Inst.getOperand(2).getRegister().get().asUint32()
  );
}

static void exec_ORI(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(Opc == RISCV::ORI);

  Inst.getOperand(0).getRegister().set(
          Inst.getOperand(1).getRegister().get().asUint32()
          | (uint32_t)Inst.getOperand(2).getImm()
  );
}



static void exec_SHIFT(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::SLLI
         || Opc == RISCV::C_SLLI
         || Opc == RISCV::SLL

         || Opc == RISCV::SRA
         || Opc == RISCV::SRAI
         || Opc == RISCV::C_SRAI

         || Opc == RISCV::SRL
         || Opc == RISCV::SRLI
         || Opc == RISCV::C_SRLI
         );

  APInt Val = Inst.getOperand(1).getRegister().get().asAPInt();
  int32_t Shift;


  uint32_t newVal;
  switch (Opc) {
  default:
    llvm_unreachable("Not implemented");
  case RISCV::SLL:
  case RISCV::SRL:
  case RISCV::SRA:

    Shift = Inst.getOperand(2).getRegister().get().asUint32();
    break;
  case RISCV::SLLI:
  case RISCV::C_SLLI:
  case RISCV::C_SRAI:
  case RISCV::SRAI:
  case RISCV::SRLI:
      Shift = Inst.getOperand(2).getImm();
    break;
  }

  //Only 6 bits
  Shift &= 0x1F;

  dbgs() << "Shift By" << Shift << "\n";

  switch (Opc) {
  default:
    llvm_unreachable("Not implemented");
  case RISCV::SLL:
  case RISCV::SLLI:
  case RISCV::C_SLLI:
    newVal = Val.shl(Shift).getZExtValue();
    break;
  case RISCV::C_SRAI:
  case RISCV::SRAI:
  case RISCV::SRA:
      newVal = Val.ashr(Shift).getZExtValue();
    break;
  case RISCV::C_SRLI:
  case RISCV::SRLI:
  case RISCV::SRL:
      newVal = Val.lshr(Shift).getZExtValue();
     break;
  }

  Inst.getOperand(0).getRegister().set(newVal);


  dbgs() << "NewVal: " << newVal << " (0x";
  dbgs().write_hex(newVal);
  dbgs() << ") = Shift logical? left? " << Val
         << " By " << Shift << "\n";
}

static void exec_C_ADD(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();

  assert(   Opc == RISCV::C_ADD
         || Opc == RISCV::ADD);


  uint32_t RHS1 = Inst.getOperand(1).getRegister().get().asUint32();
  uint32_t RHS2 = Inst.getOperand(2).getRegister().get().asUint32();


  Inst.getOperand(0).getRegister().set(RHS1 + RHS2);
  dbgs() << RHS1 << " + " << RHS2 << " = " << RHS1 + RHS2;
  dbgs() << "\n";
}

static void exec_STORE(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::SB
         || Opc == RISCV::SH
         || Opc == RISCV::SW
         || Opc == RISCV::C_SW
         || Opc == RISCV::C_SWSP

            );


  uint32_t Addr      = Inst.getOperand(1).getRegister().get().asUint32();
  int32_t AddrOffset = Inst.getOperand(2).getImm();
  if (Opc == RISCV::C_SWSP) {
//    AddrOffset *= 4;
  }

  auto Val = Inst.getOperand(0).getRegister().get();
  uint32_t V;

  Memory& Mem = Ctx.getMemory();

  size_t Size;
  switch (Opc) {
  default: llvm_unreachable("Unimplemented");
  case RISCV::SB:
    Size = 1;
//    V = Val.asUint32();
    Mem.write(Addr + AddrOffset, ArrayRef<uint8_t>(Val.getData().data(), Size));
    break;
  case RISCV::SH:
    Size = 2;
    Mem.write(Addr + AddrOffset, ArrayRef<uint8_t>(Val.getData().data(), Size));
    break;
  case RISCV::C_SW:
  case RISCV::C_SWSP:
  case RISCV::SW:
    Size = 4;
    Mem.write(Addr + AddrOffset, ArrayRef<uint8_t>(Val.getData().data(), Size));
    break;
  }


  MemoryAccessResult mar = Mem.read(Addr + AddrOffset, 4);


  dbgs() << "Store to Addr: 0x";
  dbgs().write_hex(Addr + AddrOffset);
  dbgs() << " Reg: 0x";
  dbgs().write_hex(Addr);
  dbgs() << " Offset: " << AddrOffset;
  dbgs() << " Val: " << Val.asUint32() << "(0x";
  dbgs().write_hex(Val.asUint32());
  dbgs() << ") Stored: 0x";

  dbgs().write_hex(mar.asUint32());

/*
  switch (Size) {
  default: llvm_unreachable("Unimplemented");
  case 1: dbgs().write_hex(mar.asInt8()); break;
  case 2: dbgs().write_hex(mar.asInt16()); break;
  case 4: dbgs().write_hex(mar.asInt32()); break;
  }
*/
  dbgs() << "\n";
}

static void exec_LOAD(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::LW
         || Opc == RISCV::C_LW
         || Opc == RISCV::C_LWSP
         || Opc == RISCV::LBU
         || Opc == RISCV::LB
         || Opc == RISCV::LHU
         || Opc == RISCV::LH
         );


  uint32_t Addr       = Inst.getOperand(1).getRegister().get().asUint32();
  int32_t AddrOffset = Inst.getOperand(2).getImm();
  if (Opc == RISCV::C_LWSP) {
//    AddrOffset *= 4;
  }


  Memory& Mem = Ctx.getMemory();

  size_t Size;
  uint32_t LoadedVal;

  switch (Opc) {
  default: llvm_unreachable("Unimplemented");

  case RISCV::LBU:
      Size = 1;
      LoadedVal = Mem.read(Addr + AddrOffset, Size).asUint8();
      break;

  case RISCV::LB:
    Size = 1;
    LoadedVal = Mem.read(Addr + AddrOffset, Size).asInt8();
    break;

  case RISCV::LHU:
    Size = 2;
    LoadedVal = Mem.read(Addr + AddrOffset, Size).asUint16();
    break;
  case RISCV::LH:
    Size = 2;
    LoadedVal = Mem.read(Addr + AddrOffset, Size).asInt16();
    break;
  case RISCV::C_LW:
  case RISCV::C_LWSP:
  case RISCV::LW:
    Size = 4;
    LoadedVal = Mem.read(Addr + AddrOffset, Size).asUint32();
    break;
  }

  Inst.getOperand(0).getRegister().set(
        LoadedVal
  );


  dbgs() << "Load from Addr: 0x";
  dbgs().write_hex(Addr + AddrOffset);
  dbgs() << " Reg: 0x";
  dbgs().write_hex(Addr);
  dbgs() << " Offset: " << AddrOffset;
  dbgs() << " Val: " << LoadedVal << " (0x";
  dbgs().write_hex(LoadedVal);
  dbgs() << ")\n";
}

static void exec_CSRRS(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(    Opc == RISCV::CSRRS
          || Opc == RISCV::CSRRSI);

  uint32_t CsrId = Inst.getOperand(1).getImm();

  dbgs() << "CsrID: 0x";
  dbgs().write_hex(CsrId);
  dbgs() << "\n";


  RISCVLLRRegisterFile *Ctx_ptr = static_cast<RISCVLLRRegisterFile*>(&Ctx.getRegisterFile());

  LLRRegister & CSRReg = Ctx_ptr->getCSR(CsrId);

  uint32_t CSRVal = CSRReg.get().asUint32();


  uint32_t CSR_NewVal;
  if (Opc == RISCV::CSRRS) {
    CSR_NewVal = Inst.getOperand(2).getRegister().get().asUint32();
  } else {
    CSR_NewVal = Inst.getOperand(2).getImm();
  }


  Inst.getOperand(0).getRegister().set(CSRVal);

  CSRReg.set(CSRVal | CSR_NewVal);

  dbgs() << "New Csr Val: 0x";
  dbgs().write_hex(CSRVal | CSR_NewVal);
  dbgs() << "\n";


  dbgs() << "!!!XXXCSR is dummy implemented\n";
}

static void exec_CSRRC(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(    Opc == RISCV::CSRRC
             || Opc == RISCV::CSRRCI);

  uint32_t CsrId = Inst.getOperand(1).getImm();

  dbgs() << "CsrID: 0x";
  dbgs().write_hex(CsrId);
  dbgs() << "\n";

  RISCVLLRRegisterFile *Ctx_ptr = static_cast<RISCVLLRRegisterFile*>(&Ctx.getRegisterFile());

  LLRRegister & CSRReg = Ctx_ptr->getCSR(CsrId);
  uint32_t CSRVal = CSRReg.get().asUint32();


  uint32_t CSR_NewVal;
  if (Opc == RISCV::CSRRC) {
    CSR_NewVal = Inst.getOperand(2).getRegister().get().asUint32();
  } else {
    CSR_NewVal = Inst.getOperand(2).getImm();
  }


  Inst.getOperand(0).getRegister().set(CSRVal);

  CSRReg.set(CSRVal & ~CSR_NewVal);

  dbgs() << "New Csr Val: 0x";
  dbgs().write_hex(CSRVal & ~CSR_NewVal);
  dbgs() << "\n";


  dbgs() << "!!!XXXCSR is dummy implemented\n";
}


static void exec_CSRRW(LLRContext& Ctx, LLRInst& Inst) {
  unsigned Opc = Inst.getOpcode();
  assert(   Opc == RISCV::CSRRW
         || Opc == RISCV::CSRRWI);

  uint32_t CsrId = Inst.getOperand(1).getImm();

  dbgs() << "CsrID: 0x";
  dbgs().write_hex(CsrId);
  dbgs() << "\n";

  RISCVLLRRegisterFile *Ctx_ptr = static_cast<RISCVLLRRegisterFile*>(&Ctx.getRegisterFile());

  LLRRegister & CSRReg = Ctx_ptr->getCSR(CsrId);
  uint32_t CSRVal = CSRReg.get().asUint32();

  Inst.getOperand(0).getRegister().set(CSRVal);

  uint32_t newVal;
  if (Opc == RISCV::CSRRW) {
    newVal = Inst.getOperand(2).getRegister().get().asUint32();
  } else {
    newVal = Inst.getOperand(2).getImm();
  }

  CSRReg.set(newVal);

  dbgs() << "New Csr Val: 0x";
  dbgs().write_hex(newVal);
  dbgs() << "\n";
}

static void exec_ECALL(LLRContext& Ctx, LLRInst& Inst) {
    unsigned Opc = Inst.getOpcode();
    assert(Opc == RISCV::ECALL);

    uint32_t status = Ctx.getRegisterFile().getRegisterById(RISCV::X3).get().asUint32();
    RISCVLLRRegisterFile *Ctx_ptr = static_cast<RISCVLLRRegisterFile*>(&Ctx.getRegisterFile());

    //TODO consider priv mode ucause etc
    LLRRegister &PC = Ctx.getRegisterFile().getPC();

    Ctx_ptr->getCSR(RISCV_CSR::mcause).set(PC.get().getData());

    uint32_t newPCVal =  Ctx_ptr->getCSR(RISCV_CSR::mtvec).get().asUint32();


    PC.set(newPCVal);
    Ctx.setBranch(true);

    uint32_t gpVal = Ctx_ptr->getRegisterById(RISCV::X3).get().asUint32();

    dbgs() << "ECALL to 0x";
    dbgs().write_hex(newPCVal);
    dbgs() << " gp:" <<  gpVal << "\n";


    exit(gpVal);
}

static void exec_xRET(LLRContext& Ctx, LLRInst& Inst) {
    unsigned Opc = Inst.getOpcode();
    assert(Opc == RISCV::MRET
        || Opc == RISCV::SRET);

    RISCVLLRRegisterFile *Ctx_ptr = static_cast<RISCVLLRRegisterFile*>(&Ctx.getRegisterFile());


    //TODO sepc, uepc
    uint32_t newPCVal;
    switch (Opc) {
      case RISCV::MRET:
        newPCVal = Ctx_ptr->getCSR(RISCV_CSR::mepc).get().asUint32();
        break;
      case RISCV::SRET:
        newPCVal = Ctx_ptr->getCSR(RISCV_CSR::sepc).get().asUint32();
        break;
      case RISCV::URET:
        newPCVal = Ctx_ptr->getCSR(RISCV_CSR::uepc).get().asUint32();
         break;
    }

    Ctx.getRegisterFile().getPC().set(newPCVal);
    Ctx.setBranch(true);

    //TODO change priv mode

    dbgs() << "xRET to 0x";
    dbgs().write_hex(newPCVal);
    dbgs() << "\n";
}

static void exec_NOP(LLRContext& Ctx, LLRInst& Inst) {
  dbgs() << "NOP or not implemented instruction\n";
}

namespace llr {
namespace llr_RISCV {
#include "RISCVGenExecutionFunctionMatcher.inc"
}
}



llr_execution_func llr::llr_RISCV::find_execution_function_by_opcode(unsigned Opc) {

    llr_execution_func execution_func = llr_RISCV::lookup(Opc);

    if (execution_func != nullptr) {
        dbgs() << "Exececution function found\n";
        return execution_func;
    } else {
        dbgs() << "Exececution function not found\n";
    }

    switch (Opc) {
        default:
            llvm_unreachable("Not implemented instruction");
        case RISCV::AUIPC:
            execution_func = exec_AUIPC;
            break;

        case RISCV::ADD:
        case RISCV::C_ADD:
            execution_func = exec_C_ADD;
            break;

        case RISCV::C_ADDI:
        case RISCV::ADDI:
            execution_func = exec_ADDI;
            break;

        case RISCV::C_ADDI4SPN:
            execution_func = exec_ADDI4SPN;
            break;

        case RISCV::DIV:
            execution_func = exec_DIV;
            break;

        case RISCV::SUB:
        case RISCV::C_SUB:
            execution_func = exec_C_SUB;
            break;

        case RISCV::C_LI:
            execution_func = exec_C_LI;
            break;

        case RISCV::C_LUI:
            execution_func = exec_C_LUI;
            break;

        case RISCV::LUI:
            execution_func = exec_LUI;
            break;

        case RISCV::JALR:
            execution_func = exec_JALR;
            break;


        case RISCV::JAL:
            execution_func = exec_JAL;
            break;

        case RISCV::C_JAL:
            execution_func = exec_C_JAL;
            break;

        case RISCV::C_J:
            execution_func = exec_J;
            break;

        case RISCV::C_JALR:
        case RISCV::C_JR:
            execution_func = exec_JR;
            break;


        case RISCV::C_MV:
            execution_func = exec_C_MV;
            break;

        case RISCV::BNE:
        case RISCV::BLTU:
        case RISCV::BLT:
        case RISCV::BGEU:
        case RISCV::BEQ:
        case RISCV::BGE:
            execution_func = exec_BG;
            break;

        case RISCV::SLTI:
        case RISCV::SLTIU:

        case RISCV::SLT:
        case RISCV::SLTU:
            execution_func = exec_SLT;
            break;

        case RISCV::XORI:
            execution_func = exec_XORI;
            break;
        case RISCV::XOR:
            execution_func = exec_XOR;
            break;


        case RISCV::AND:
            execution_func = exec_AND;
            break;

        case RISCV::C_ANDI:
        case RISCV::ANDI:
            execution_func = exec_ANDI;
            break;

        case RISCV::C_OR:
        case RISCV::OR:
            execution_func = exec_OR;
            break;

        case RISCV::ORI:
            execution_func = exec_ORI;
            break;

        case RISCV::C_BEQZ:
        case RISCV::C_BNEZ:
            execution_func = exec_C_BEQZ;
            break;

        case RISCV::SLL:
        case RISCV::SLLI:
        case RISCV::C_SLLI:

        case RISCV::SRA:
        case RISCV::SRAI:
        case RISCV::C_SRAI:

        case RISCV::SRL:
        case RISCV::SRLI:
        case RISCV::C_SRLI:
            execution_func = exec_SHIFT;
            break;

        case RISCV::SB:
        case RISCV::SH:
        case RISCV::C_SW:
        case RISCV::C_SWSP:
        case RISCV::SW:
            execution_func = exec_STORE;
            break;

        case RISCV::LB:
        case RISCV::LBU:
        case RISCV::LH:
        case RISCV::LHU:
        case RISCV::C_LW:
        case RISCV::C_LWSP:
        case RISCV::LW:
            execution_func = exec_LOAD;
            break;

        case RISCV::CSRRCI:
        case RISCV::CSRRC:
            execution_func = exec_CSRRC;
            break;


        case RISCV::CSRRSI:
        case RISCV::CSRRS:
            execution_func = exec_CSRRS;
            break;

        case RISCV::CSRRWI:
        case RISCV::CSRRW:
            execution_func = exec_CSRRW;
            break;

        case RISCV::ECALL:
            execution_func = exec_ECALL;
            break;


        case RISCV::URET:
        case RISCV::SRET:
        case RISCV::MRET:
            execution_func = exec_xRET;
            break;

        case RISCV::FENCE_I:
        case RISCV::FENCE:
            execution_func = exec_NOP;
    }
  return execution_func;
}

