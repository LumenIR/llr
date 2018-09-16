//===- llr/Fetcher/LLRFethcer.h - Instruction fetcher interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_TARGET_RISCV_RISCVLLRFETCHER_H
#define LLR_TARGET_RISCV_RISCVLLRFETCHER_H

#include "llr/Fetcher/LLRFetcher.h"

namespace llr {

class MemoryAccessResult;
class LLRContext;


class RISCVLLRFetcher : public LLRFetcher {
public:
  virtual MemoryAccessResult fetchNext(const LLRContext&) const override;

}; // class RISCVLLRFetcher

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRFETCHER_H
