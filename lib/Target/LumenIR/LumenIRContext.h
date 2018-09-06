#ifndef LLR_TARGET_LUMENIR_LUMENIRCONTEXT_H
#define LLR_TARGET_LUMENIR_LUMENIRCONTEXT_H

#include "llr/Context/LLRContextBase.h"

namespace llr
{

class Stack;
class Memory;
class RegisterFile;

class LumenIRLLRContext : public LLRContextBase {

public:
  LumenIRLLRContext(Memory *m, RegisterFile *r, Stack *s) :
    LLRContextBase(m, r, s)
  { }


  virtual bool isRunning() const override {
    return true;
  }


}; // class LumenIRLLRContext

} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRCONTEXT_H

