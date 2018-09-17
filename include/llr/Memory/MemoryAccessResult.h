//===- llr/Memory/MemoryAccessResult.h - Memory access result -*- C++ -*  -===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_MEMORY_MEMORYACCESSRESULT_H
#define LLR_MEMORY_MEMORYACCESSRESULT_H

#include "llr/Memory/MemoryAddress.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include <vector>
#include <cassert>
#include <cstdint>

//namespace llvm {
//  class ArrayRef;
//}

namespace llr {

enum class MemoryAccessStatus {
  Forbidden,
  NotFound,
  Uninit,
  ReadOK,
  WriteOK
};


class MemoryAccessResult {
  using MAS = enum MemoryAccessStatus;
public:

  MemoryAccessResult(MAS S, MemoryAddress Addr) :
    Address(Addr),
    Status(S) {

  }


  //TODO make MemoryAccessResult builder to remove double copy
  MemoryAccessResult(MAS S, llvm::ArrayRef<uint8_t> d, MemoryAddress Address);


  MemoryAccessStatus getStatus() {
    return Status;
  }

  size_t getSize() const {
    return data.size();
  }

  llvm::ArrayRef<uint8_t> getData() const {
    assert(Status == MAS::ReadOK && "Trying to access data of failed memory read");
    return data;
  }

  const MemoryAddress & getAddress() const {
    return Address;
  }

  void dump() const {
    print(llvm::dbgs());
  }

  void print(llvm::raw_ostream &OS) const {
    OS << "MAR ";
    switch (Status) {
    case MAS::Forbidden: OS << "Forbidden"; break;
    case MAS::NotFound:  OS << "NotFound "; break;
    case MAS::ReadOK:    OS << "ReadOK   "; break;
    case MAS::WriteOK:   OS << "WriteOK  "; break;
    default:        OS << "Unknown Status"; break;
    }
    OS << "\n";

    for(int i = 0; i < data.size(); ++i) {
      OS << "0x";
      OS.write_hex(Address + i);
      OS << " 0x";
      OS.write_hex(data[i]);
      OS << "\n";
    }
  }

public:
  MemoryAddress Address;
  MemoryAccessStatus Status;
  std::vector<uint8_t> data;

}; // class MemoryAccessResult

} // end namespace llr

#endif //LLR_MEMORY_MEMORYACCESSRESULT_H

