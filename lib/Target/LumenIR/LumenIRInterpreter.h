#ifndef LLR_TARGET_LUMENIR_LUMENIRINTERPRETER_H
#define LLR_TARGET_LUMENIR_LUMENIRINTERPRETER_H

#include "llr/Interpreter/Interpreter.h"

namespace llr {

class LLRContext;
class LLRFetcher;
class LLRDecoder;


class LumenIRInterpreter : Interpreter {
public:
  LumenIRInterpreter(LLRContext&, LLRFetcher&, LLRDecoder&);




}; // class Interpeter

} // end namespace llr

#endif //LLR_TARGET_LUMENIR_LUMENIRINTERPRETER_H
