//===- llr/Decoder/Decoder.h - Instruction decoder interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_DECODER_LLRDECODER_H
#define LLR_DECODER_LLRDECODER_H

#include "llr/Instruction/LLRInst.h"

#include "llvm/ADT/ArrayRef.h"

namespace llr {

class LLRInst;
class MemoryAddress;

class LLRDecoder {
public:

  virtual ~LLRDecoder() = default;

  virtual LLRInst decode(llvm::ArrayRef<uint8_t> data, const MemoryAddress &Address) const = 0;

}; // class LLRDecoder

} // end namespace llr

#endif //LLR_DECODER_LLRDECODER_H
