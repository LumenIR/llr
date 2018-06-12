//===- llr/Interpeter/Interpeter.h ---- Interpeter interface --*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLR_INTERPETER_INTERPETER_H
#define LLR_INTERPETER_INTERPETER_H

namespace llr {

class Context;
class Fetcher;
class Decoder;


class Interpeter {
public:
  Interpeter(Context&, Fetcher&, Decoder&);
  virtual ~Interpeter() = default;

  void run();

private:
  Context &Ctx;
  Fetcher &fetcher;
  Decoder &decoder;

}; // class Interpeter

} // end namespace llr

#endif //LLR_INTERPETER_INTERPETER_H
