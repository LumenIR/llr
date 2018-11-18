//===- lib/Target/RISCV/RISCVLLRExecutionFunctions.h ---------*- C++ -*-----===//
//
//                     The LLVM LLR Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVLLREXECUTIIONFUNCTIONS_H
#define LLR_TARGET_RISCV_RISCVLLREXECUTIIONFUNCTIONS_H

#include "llr/Instruction/LLRInst.h"

namespace llr {
namespace llr_RISCV {

  //TODO rename
  llr_execution_func find_execution_function_by_opcode(unsigned Opc);

}
} //namespace llr



#endif //LLR_TARGET_RISCV_RISCVLLREXECUTIIONFUNCTIONS_H

