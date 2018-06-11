#include "llr/Memory/MemoryAccessResult.h"

#include <algorithm>

using namespace llr;
using namespace llvm;

MemoryAccessResult::MemoryAccessResult(MAS S, ArrayRef d) {
  Status = S;
  data.resize(d.size());
  std::copy(d.begin(), d.end(), data.begin());
}
