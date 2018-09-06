#include "llr/Target/LLRTargetRegistry.h"
#include "llr/Target/LLRTarget.h"

#include <algorithm>
#include <vector>

using namespace llvm;


namespace llr {
namespace registry {

static std::vector<LLRTarget*> targets;


void registerTarget(llvm::Triple triple, LLRTarget*(func)()) {
  //TODO check if allready exists
  targets.push_back(func());
}

LLRTarget * getLLRTarget(llvm::Triple triple) {


  auto it = std::find_if(targets.begin(), targets.end(), [triple] (LLRTarget *target) { return target->getTargetTriple() == triple; });

  if (it != targets.end()) {
    return *it;
  } else {
    return nullptr;
  }
}


}
}
