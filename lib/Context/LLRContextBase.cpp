#include "llr/Context/LLRContextBase.h"

#include "llr/Memory/Memory.h"
#include "llr/Registers/RegisterFile.h"
#include "llr/Stack/Stack.h"

using namespace llr;
using namespace llvm;

LLRContextBase::LLRContextBase(Memory *M, RegisterFile *RF, Stack *S) :
  Mem_ptr(M),
  RegisterFile_ptr(RF),
  Stack_ptr(S)
{ }


Memory & LLRContextBase::getMemory() const {
  return *Mem_ptr;
}

RegisterFile & LLRContextBase::getRegisterFile() const {
  return *RegisterFile_ptr;
}

Stack & LLRContextBase::getStack() const {
  return *Stack_ptr;
}

