//===- InstrInfoEmitter.cpp - Generate a Instruction Set Desc. --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This tablegen backend is responsible for emitting a description of the target
// instruction set for the code generator.
//
//===----------------------------------------------------------------------===//


#include "TableGenBackends.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TableGen/Error.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/TableGenBackend.h"
#include <cassert>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace llvm;

namespace {

class ExecutionInstructionMatcher {


}; // class ExecutionInstructionMatcher

} // end anonymous namespace



namespace llr {

void EmitExecutionFunctionMatcher(RecordKeeper &RK, raw_ostream &OS) {

  emitSourceFileHeader("Match llvm instruction opcode with function for interpretation", OS);

/*
  for(auto &claz : RK.getClasses()) {
    OS << claz.first << "\n";
  }
  RK.dump();
*/

  std::map<std::string, std::vector<Record*>> exec_funcs;

  for(Record* rec: RK.getAllDerivedDefinitions("Instruction")) {
    StringRef name = rec->getName();

    RecordVal* val = rec->getValue("exec_func");
    if (val != nullptr) {
      std::string func = val->getValue()->getAsUnquotedString();
      exec_funcs[func].push_back(rec);
      //OS << name << ": " <<  << "\n";
    }
  }


  OS << "llr_execution_func lookup(unsigned Opc) {\n";
  OS << "  llr_execution_func exec_func;\n";
  OS << "  switch(Opc) {\n";
  for(const auto &it : exec_funcs) {
    std::string func = it.first;

    for(const auto &inst_it : it.second) {
      RecordVal* ns = inst_it->getValue("Namespace");
      if (ns == nullptr) {
        continue;
      }

      OS << "  case " << ns->getValue()->getAsUnquotedString() << "::" << inst_it->getName() << ":\n";
    }
      OS << "    exec_func = " << func << "; break; \n";

  }
  OS << "  default: exec_func = nullptr;\n";
  OS << "  }\n";
  OS << "  return exec_func;\n";
  OS << "}\n";



//  std::vector<Record*> Defs = RK.getAllDerivedDefinitions("Intrinsic");



}

} // end llvm namespace
