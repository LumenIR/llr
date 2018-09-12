#ifndef LLR_TARGET_RISCV_RISCVINTERPRETER_H
#define LLR_TARGET_RISCV_RISCVINTERPRETER_H

#include "llr/Interpreter/Interpreter.h"

namespace llr {

class LLRContext;
class LLRFetcher;
class LLRDecoder;


class RISCVInterpreter : Interpreter {
public:
  RISCVInterpreter(LLRContext&, LLRFetcher&, LLRDecoder&);




}; // class Interpeter

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVINTERPRETER_H
