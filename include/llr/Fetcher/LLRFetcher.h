//===- llr/Fetcher/LLRFethcer.h - Instruction fetcher interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_FETCHER_LLRFETCHER_H
#define LLR_FETCHER_LLRFETCHER_H

namespace llr {

class MemoryAccessResult;
class LLRContext;


class LLRFetcher {
public:

  virtual ~LLRFetcher() = default;

  virtual MemoryAccessResult fetchNext(const LLRContext&) const = 0;

}; // class Fetcher

} // end namespace llr

#endif //LLR_FETCHER_LLRFETCHER_H
