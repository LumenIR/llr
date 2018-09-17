#include "RISCVLLRRegisterFile.h"

#include "llr/Registers/SimpleRegister.h"
#include "llr/Registers/ProxyRegister.h"

using namespace llvm;
using namespace llr;


RISCVLLRRegisterFile::RISCVLLRRegisterFile() {
  PC = new SimpleRegister(0, 0, 4);
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


