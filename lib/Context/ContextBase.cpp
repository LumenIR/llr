#include "ContextBase.h"

#include "llr/Memory/Memory.h"
#include "llr/Registers/RegisterFile.h"
#include "llr/Stack/Stack.h"

using namespace llr;
using namespace llvm;

ContextBase::ContextBase(Memory *M, RegisterFile *RF, Stack *S) :
  Mem_ptr(M),
  RegisterFile_ptr(RF),
  Stack_ptr(S)
{ }


Memory & ContextBase::getMemory() const {
  return *Mem_ptr;
}

RegisterFile & ContextBase::getRegisterFile() const {
  return *RegisterFile_ptr;
}

Stack & ContextBase::getStack() const {
  return *Stack_ptr;
}

