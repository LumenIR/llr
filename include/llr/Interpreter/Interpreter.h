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

class Context;
class Fetcher;
class Decoder;


class Interpreter {
public:
  Interpreter(Context&, Fetcher&, Decoder&);
  virtual ~Interpreter() = default;

  void run();

private:
  Context &Ctx;
  Fetcher &fetcher;
  Decoder &decoder;

}; // class Interpeter

} // end namespace llr

#endif //LLR_INTERPRETER_INTERPRETER_H
