//===- llr/Interpeter/Interpeter.h ---- Interpeter interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_INTERPRETER_LLRINTERPRETER_H
#define LLR_INTERPRETER_LLRINTERPRETER_H

namespace llr {

class LLRContext;
class LLRFetcher;
class LLRDecoder;


class LLRInterpreter {
public:
  LLRInterpreter(LLRContext*, LLRFetcher*, LLRDecoder*);
  virtual ~LLRInterpreter() = default;

  void run();

private:
  LLRContext *Ctx;
  LLRFetcher *fetcher;
  LLRDecoder *decoder;

}; // class Interpeter

} // end namespace llr

#endif //LLR_INTERPRETER_LLRINTERPRETER_H
