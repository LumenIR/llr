//===- llr/Fetcher/Fethcer.h - Instruction fetcher interface ----*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_FETCHER_FETCHER_H
#define LLR_FETCHER_FETCHER_H

namespace llr {

class MemoryAccessResult;
class Context;


class Fetcher {
public:

  virtual ~Fetcher() = default;

  virtual MemoryAccessResult fetchNext(const Context&) const = 0;

}; // class Fetcher

} // end namespace llr

#endif //LLR_FETCHER_FETCHER_H
