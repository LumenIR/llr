//===- tools/llr/llr.cpp - ------------------------------------------------===//
//
//                             The LLVM Linker
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// TODO
//
//===----------------------------------------------------------------------===//

#include "llr/Driver/LlrDriver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Object/ELFObjectFile.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/Object/Binary.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/Errc.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"

//using namespace llr;
using namespace llvm;
using namespace llvm::sys;
using namespace llvm::object;



static const Target *getTarget(const ObjectFile *Obj = nullptr) {
  // Figure out the target triple.
  llvm::Triple TheTriple("unknown-unknown-unknown");
  std::string TripleName("lumenir-unknown-unknown");
  std::string ArchName = "lumenir";

  if (TripleName.empty()) {
   if (Obj) {
     auto Arch = Obj->getArch();
     TheTriple.setArch(Triple::ArchType(Arch));
    } else {
        TheTriple.setTriple(Triple::normalize(TripleName));
        // Use the triple, but also try to combine with ARM build attributes.
    }
  }
  // Get the target specific parser.
  std::string Error;
  const Target *TheTarget = TargetRegistry::lookupTarget(ArchName, TheTriple,
                                                         Error);
  if (!TheTarget) {
    if (Obj) {

    } else {
      errs() << "can't find target: " << Error;
      errs() << Obj->getFileName() << "can't find target: " << Error;
      exit(1);
    }
  }

  // Update the triple name and return the found target.
  TripleName = TheTriple.getTriple();
  return TheTarget;
}

template <class ELFT> void loadFile(const ELFFile<ELFT> *o) {


}


static void LoadELF(ObjectFile *Obj) {
  const Target *TheTarget = getTarget(Obj);

  // Little-endian 32-bit
  if (const ELF32LEObjectFile *ELFObj = dyn_cast<ELF32LEObjectFile>(Obj))
    loadFile(ELFObj->getELFFile());

  // Big-endian 32-bit
  if (const ELF32BEObjectFile *ELFObj = dyn_cast<ELF32BEObjectFile>(Obj))
    loadFile(ELFObj->getELFFile());

  // Little-endian 64-bit
  if (const ELF64LEObjectFile *ELFObj = dyn_cast<ELF64LEObjectFile>(Obj))
    loadFile(ELFObj->getELFFile());

  // Big-endian 64-bit
  if (const ELF64BEObjectFile *ELFObj = dyn_cast<ELF64BEObjectFile>(Obj))
    loadFile(ELFObj->getELFFile());
}


int main(int Argc, const char **Argv) {
  // Standard set up, so program fails gracefully.
  sys::PrintStackTraceOnErrorSignal(Argv[0]);
  PrettyStackTraceProgram StackPrinter(Argc, Argv);

  //  llvm_shutdown_obj Shutdown;

  StringRef file = "a.out";

  Expected<OwningBinary<Binary>> BinaryOrErr = createBinary(file);
  if (!BinaryOrErr) {
    errs() << file << " object_error::invalid_file_type";
    exit(1);
  }
  Binary &Binary = *BinaryOrErr.get().getBinary();

  if (ObjectFile *o = dyn_cast<ObjectFile>(&Binary)) {

  } else {
    
  }
}
