//===- lib/Target/RISCV/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H
#define LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H

#include "llr/Registers/LLRRegisterFile.h"

#define GET_REGINFO_ENUM
#include "RISCVGenRegisterInfo.inc"
#undef GET_REGINFO_ENUM

#include <vector>
#include <array>
#include <unordered_map>


namespace llr {

namespace RISCV_CSR {
  enum CSR : unsigned {
    fflags = 0x001,
    frm = 0x002,
    fcsr = 0x003,

    sstatus = 0x100,
    stvec = 0x105,

    uepc = 0x041,

    sscratch = 0x140,
    sepc = 0x141,
    satp = 0x180,

    mvendorid = 0xF11,
    marchid = 0XF12,
    mhartid = 0xF14,
    mimpid = 0xF13,

    mstatus = 0x300,
    medeleg = 0x302,
    mideleg = 0x303,
    mie = 0x304,
    mtvec = 0x305,

    mepc = 0x341,
    mcause = 0x342,

    pmpcfg0 = 0x3A0,

    pmaddr0 = 0x3B0,
    pmaddr1 = 0x3B1,

  };
}

class LLRRegister;

class RISCVLLRRegisterFile : public LLRRegisterFile {
public:
  RISCVLLRRegisterFile();

  virtual ~RISCVLLRRegisterFile() = default;

  virtual LLRRegister& getRegisterById(unsigned RegisterId) const override;

  virtual LLRRegister& getPC() const override;

  LLRRegister& getCSR(unsigned csrId);

protected:
  LLRRegister *PC;

  std::array<uint8_t, 32*4> GPR_storage;
  std::array<LLRRegister*, 32> GPRRegisters;

  std::unordered_map<unsigned, LLRRegister*> CSRRegisters;
}; // class RISCVLLRRegisterFile

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRREGISTERFILE_H

