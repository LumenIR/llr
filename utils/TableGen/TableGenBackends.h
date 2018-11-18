//===- TableGenBackends.h - Declarations for LLR TableGen Backends ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations for all of the LLR TableGen
// backends. A "TableGen backend" is just a function. See
// "$LLVM_ROOT/utils/TableGen/TableGenBackends.h" for more info.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_UTILS_TABLEGEN_TABLEGENBACKENDS_H
#define LLR_UTILS_TABLEGEN_TABLEGENBACKENDS_H

#include <string>

namespace llvm {
  class raw_ostream;
  class RecordKeeper;
}

using llvm::raw_ostream;
using llvm::RecordKeeper;

namespace llr {

void EmitExecutionFunctionMatcher(RecordKeeper &RK, raw_ostream &OS);


} // end namespace llr

#endif // LLR_UTILS_TABLEGEN_TABLEGENBACKENDS_H
