#ifndef LLR_TARGET_RISCV_RISCVLLRINTERPRETER_H
#define LLR_TARGET_RISCV_RISCVLLRINTERPRETER_H

#include "llr/Interpreter/LLRInterpreter.h"

namespace llr {

class LLRContext;
class LLRFetcher;
class LLRDecoder;


class RISCVLLRInterpreter : LLRInterpreter {
public:
  RISCVLLRInterpreter(LLRContext&, LLRFetcher&, LLRDecoder&);




}; // class Interpeter

} // end namespace llr

#endif //LLR_TARGET_RISCV_RISCVLLRINTERPRETER_H
