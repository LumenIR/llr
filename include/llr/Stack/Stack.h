//===- llr/Stack/Stack.h - Stack interface --------------------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_STACK_STACK_H
#define LLR_STACK_STACK_H

#include "llvm/ADT/ArrayRef.h"

#include <cstdint>


namespace llr {

class MemoryAccessResult;


class Stack {
  using ArrayRef = llvm::ArrayRef<uint8_t>;

public:

  virtual ~Stack() = default;

  virtual MemoryAccessResult push(const ArrayRef&) const = 0;

  virtual MemoryAccessResult pop(size_t size) const = 0;


}; // class Stack

} // end namespace llr

#endif //LLR_STACK_STACK_H
