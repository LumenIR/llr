//===- lib/Target/LumenIR/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_LUMENIR_LUMENIRLLRDECODER_H
#define LLR_TARGET_LUMENIR_LUMENIRLLRDECODER_H

#include "llr/Decoder/LLRDecoder.h"

namespace llvm {
  class MCDisassembler;
}

namespace llr {

class LLRInst;
class MemoryAddress;

class LumenIRLLRDecoder : public LLRDecoder {
public:
  LumenIRLLRDecoder();


  virtual LLRInst decode(llvm::ArrayRef<uint8_t> data, const MemoryAddress &Address) const override;

private:
  llvm::MCDisassembler *disasm;


}; // class LumenIRLLRDecoder

} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRLLRDECODER_H

