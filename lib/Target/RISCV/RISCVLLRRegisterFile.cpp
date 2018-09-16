#include "RISCVLLRRegisterFile.h"

#include "llr/Registers/SimpleRegister.h"

using namespace llvm;
using namespace llr;


RISCVLLRRegisterFile::RISCVLLRRegisterFile() {
//TODO
}

LLRRegister&  RISCVLLRRegisterFile::getRegisterById(unsigned regId) const {
  switch (regId) {
//  case llvm::RISCV::PC:    return *PC;
//  case llvm::RISCV::SP:    return *SP;
//  case llvm::RISCV::FP:    return *FP;
  }
}
