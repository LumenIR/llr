#ifndef LLR_TARGET_RISCV_RISCVCONTEXT_H
#define LLR_TARGET_RISCV_RISCVCONTEXT_H

#include "llr/Context/LLRContextBase.h"

namespace llr
{

class Stack;
class Memory;
class RegisterFile;

class RISCVLLRContext : public LLRContextBase {

public:
  RISCVLLRContext(Memory *m, RegisterFile *r, Stack *s) :
    LLRContextBase(m, r, s)
  { }


  virtual bool isRunning() const override {
    return true;
  }


}; // class RISCVLLRContext

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVCONTEXT_H

