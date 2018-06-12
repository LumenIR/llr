//===- llr/Decoder/Decoder.h - Instruction decoder interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_DECODER_DECODER_H
#define LLR_DECODER_DECODER_H

#include "llvm/ADT/ArrayRef.h"


namespace llr {

class LLRInst;

class Decoder {
  using ArrayRef = llvm::ArrayRef<uint8_t>;

public:

  virtual ~Decoder() = default;

  virtual LLRInst decode(ArrayRef) const = 0;

}; // class Decoder

} // end namespace llr

#endif //LLR_DECODER_DECODER_H
