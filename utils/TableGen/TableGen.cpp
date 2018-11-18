//===- TableGen.cpp - Top-Level TableGen implementation for LLR -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the main function for LLR's TableGen.
//
//===----------------------------------------------------------------------===//

#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Signals.h"
#include "llvm/TableGen/Error.h"
#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"

using namespace llvm;
using namespace llr;

enum ActionType {
  GenLLRExecutionInstructionMatcher
};

namespace {
cl::opt<ActionType> Action(
    cl::desc("Action to perform:"),
    cl::values(
        clEnumValN(GenLLRExecutionInstructionMatcher,
                "gen-llr-execution-function-matcher",
                "Generate llr execution function matcher"))

);


bool LLRTableGenMain(raw_ostream &OS, RecordKeeper &Records) {
  switch (Action) {
  case GenLLRExecutionInstructionMatcher:
    EmitExecutionFunctionMatcher(Records, OS);
    break;

  }

  return false;
}
} // anonymous namespace

int main(int argc, char **argv) {
  sys::PrintStackTraceOnErrorSignal(argv[0]);
  PrettyStackTraceProgram X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv);

  llvm_shutdown_obj Y;

  return TableGenMain(argv[0], &LLRTableGenMain);
}

#ifdef __has_feature
#if __has_feature(address_sanitizer)
#include <sanitizer/lsan_interface.h>
// Disable LeakSanitizer for this binary as it has too many leaks that are not
// very interesting to fix. See compiler-rt/include/sanitizer/lsan_interface.h .
int __lsan_is_turned_off() { return 1; }
#endif  // __has_feature(address_sanitizer)
#endif  // defined(__has_feature)
