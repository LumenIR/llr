#include "RISCVLLRRegisterFile.h"

#include "llr/Registers/SimpleRegister.h"
#include "llr/Registers/ProxyRegister.h"
#include "llr/Registers/ZeroRegister.h"

using namespace llvm;
using namespace llr;


RISCVLLRRegisterFile::RISCVLLRRegisterFile() {

  for(unsigned CSRId : {
                        RISCV_CSR::fflags,

                        RISCV_CSR::mhartid,
                        RISCV_CSR::mstatus,
                        RISCV_CSR::mtvec,
                        RISCV_CSR::satp,
                        RISCV_CSR::pmaddr0,
                        RISCV_CSR::pmpcfg0,

                        RISCV_CSR::medeleg,
                        RISCV_CSR::mideleg,
                        RISCV_CSR::mie,
                        RISCV_CSR::mepc,
                        RISCV_CSR::mcause,

                        RISCV_CSR::sstatus,
                        RISCV_CSR::stvec,
                        RISCV_CSR::sepc,
                        RISCV_CSR::sscratch,

                        RISCV_CSR::uepc,
                        }) {

    CSRRegisters[CSRId] = new SimpleRegister(0, 0, 4);
  }



  GPRRegisters[0] = new ZeroRegister(RISCV::X0, RISCV::GPRRegClassID, 4);

  for (int i = 1; i < 32; ++i) {
    GPRRegisters[i] = new ProxyRegister(RISCV::X0 + i, RISCV::GPRRegClassID, 4, GPR_storage.data() + 4 * i);
  }

  PC = new SimpleRegister(0, 0, 4);
}


LLRRegister& RISCVLLRRegisterFile::getCSR(unsigned csrId) {
  auto it = CSRRegisters.find(csrId);
  assert(it != CSRRegisters.end());

  return *it->second;
}


LLRRegister&  RISCVLLRRegisterFile::getRegisterById(unsigned regId) const {

  if (regId >= RISCV::X0 && regId <= RISCV::X31) {
    return *GPRRegisters[regId - RISCV::X0];
  }
  llvm_unreachable("Unknown register");
}

LLRRegister& RISCVLLRRegisterFile::getPC() const {
 return *PC;
}


