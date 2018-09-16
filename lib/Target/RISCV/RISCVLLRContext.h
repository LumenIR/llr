#ifndef LLR_TARGET_RISCV_RISCVLLRCONTEXT_H
#define LLR_TARGET_RISCV_RISCVLLRCONTEXT_H

#include "llr/Context/LLRContextBase.h"

namespace llr
{

class Stack;
class Memory;
class LLRRegisterFile;

class RISCVLLRContext : public LLRContextBase {

public:
  RISCVLLRContext(Memory *m, LLRRegisterFile *r, Stack *s) :
    LLRContextBase(m, r, s)
  { }


  virtual bool isRunning() const override {
    return true;
  }


}; // class RISCVLLRContext

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRCONTEXT_H

