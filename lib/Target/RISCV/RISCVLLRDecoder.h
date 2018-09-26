//===- lib/Target/RISCV/RegisterFile.h ---------------------*- C++ -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVLLRDECODER_H
#define LLR_TARGET_RISCV_RISCVLLRDECODER_H

#include "llr/Decoder/LLRDecoder.h"

#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCInstPrinter.h"


namespace llvm {
  class MCDisassembler;
}

namespace llr {

class LLRInst;
class LLRContext;
class MemoryAddress;

class RISCVLLRDecoder : public LLRDecoder {
public:
  RISCVLLRDecoder();


  virtual LLRInst decode(llvm::ArrayRef<uint8_t> data, const MemoryAddress &Address, LLRContext &Ctx) const override;

private:
  std::unique_ptr<llvm::MCDisassembler> disasm;
  std::unique_ptr<llvm::MCStreamer> Streamer;

  std::unique_ptr<llvm::MCSubtargetInfo> STI;
  std::unique_ptr<llvm::MCInstPrinter> IP;

  std::unique_ptr<llvm::MCRegisterInfo> MRI;
  std::unique_ptr<llvm::MCAsmInfo> MAI;

  std::unique_ptr<llvm::MCInstrInfo> MCII;


}; // class RISCVLLRDecoder

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRDECODER_H

