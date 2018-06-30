#include "LumenIRRegisterFile.h"

#include "llr/Registers/SimpleRegister.h"

using namespace llvm;
using namespace llr;


LumenIRRegisterFile::LumenIRRegisterFile() {
  PC = new SimpleRegister(LumenIR::PC, 0, 32);
  SP = new SimpleRegister(LumenIR::SP, 0, 32);
  FP = new SimpleRegister(LumenIR::FP, 0, 32);


}

Register&  LumenIRRegisterFile::getRegisterById(unsigned regId) const {
  switch (regId) {
  case llvm::LumenIR::PC:    return *PC;
  case llvm::LumenIR::SP:    return *SP;
  case llvm::LumenIR::FP:    return *FP;
  }
}
