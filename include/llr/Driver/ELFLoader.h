//===- llr/Driver/ELFLoader.h - ELFLoader ---------------------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_DRIVER_ELFLOADER_H
#define LLR_DRIVER_ELFLOADER_H

namespace llvm {

class StringRef;

}

namespace llr {

class LLRContext;


class ELFLoader {
public:

  virtual ~ELFLoader() = default;

  virtual loadFile(llvm::StringRef, LLRContext&) const = 0;

}; // class ELFLoader

} // end namespace llr

#endif //LLR_DRIVER_ELFLOADER_H
