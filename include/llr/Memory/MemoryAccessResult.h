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


namespace llvm {
  class ArrayRef;
}

namespace llr {

class enum MemoryAccessStatus {
  MAS_Forbidden,
  MAS_ReadOK,
  MAS_WriteOK
};


class MemoryAccessResult {

public:
  MemoryAccessStatus getStatus();
  size_t getSize();

  ArrayRef getData();

public:

}; // class MemoryAccessResult

} // end namespace llr

#endif //LLR_MEMORY_MEMORYACCESSRESULT_H

