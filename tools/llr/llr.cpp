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
#include "llr/Driver/ELFLoader.h"
#include "llr/Target/LLRTarget.h"
#include "llr/Interpreter/LLRInterpreter.h"
#include "llr/Target/LLRTargetRegistry.h"

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
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdint>

using namespace llr;
using namespace llvm;
using namespace llvm::sys;
using namespace llvm::object;



static const Target *getTarget(const ObjectFile *Obj = nullptr) {
  // Figure out the target triple.
  llvm::Triple TheTriple("unknown-unknown-unknown");
  std::string TripleName("riscv-unknown-unknown");
  std::string ArchName = "riscv";

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


namespace llr {
void report_fatal_error(void *UserData, const std::string & Problem, bool GenCrashDiag);
}

int main(int Argc, const char **Argv) {
  // Standard set up, so program fails gracefully.
  sys::PrintStackTraceOnErrorSignal(Argv[0]);
  PrettyStackTraceProgram StackPrinter(Argc, Argv);

  install_fatal_error_handler(llr::report_fatal_error, nullptr);

  cl::ParseCommandLineOptions(Argc, Argv);

  //  llvm_shutdown_obj Shutdown;

  StringRef file = "a.out";

  ELFLoader loader;

//  InitializeAllTargets();

  // Initialize targets and assembly printers/parsers.
  InitializeAllTargetInfos();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();
  InitializeAllDisassemblers();


  registry::InitializeAllLLRTargets();

  LLRTarget *llrTarget = registry::getLLRTarget(Triple("riscv"));

  loader.loadFile(file, llrTarget->getContext());

  llrTarget->getInterpeter().run();
}

void llr::report_fatal_error(void *UserData, const std::string & Problem, bool GenCrashDiag) {
  errs() << "llr fatal error: " << Problem << "\n";
}
