//===- llr/Interpeter/Interpeter.h ---- Interpeter interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_INTERPRETER_INTERPRETER_H
#define LLR_INTERPRETER_INTERPRETER_H

namespace llr {

class LLRContext;
class LLRFetcher;
class LLRDecoder;


class Interpreter {
public:
  Interpreter(LLRContext*, LLRFetcher*, LLRDecoder*);
  virtual ~Interpreter() = default;

  void run();

private:
  LLRContext *Ctx;
  LLRFetcher *fetcher;
  LLRDecoder *decoder;

}; // class Interpeter

} // end namespace llr

#endif //LLR_INTERPRETER_INTERPRETER_H
