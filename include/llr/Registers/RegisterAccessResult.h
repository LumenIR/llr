//===- llr/Registers/RegisterAccessResult.h - Memory access result-*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_REGISTERS_REGISTERACESSSRESULT_H
#define LLR_REGISTERS_REGISTERACCESSRESULT_H

namespace llvm {
  class ArrayRef;
  class APInt;
  class APFloat;
}

namespace llr {

class enum RegisterAccessStatus {
  RAS_Forbidden,
  RAS_ReadOk,
  RAS_WriteOk
};

class RegisterAccessResult {
  using APFloat = llvm::APFloat;
  using APInt = llvm::APInt;
  using ArrayRef = llvm::ArrayRef;


public:
  RegisterAccessStatus getStatus();
  size_t getSize();

  //TODO std::vector/array or llvm::SmallVector
  ArrayRef getData();

  APFloat getAPFloat();
  APInt getAPInt();

}; // class RegisterAccessResult

} // end namespace llr

#endif //LLR_REGISTERS_REGISTERACCESSRESULT_H

