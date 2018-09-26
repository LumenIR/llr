#include "llr/Registers/ZeroRegister.h"
#include "llr/Registers/RegisterAccessResult.h"

#include <cassert>
#include <cstdint>
#include <algorithm>

using namespace llvm;
using namespace llr;

using SetMode = llr::LLRRegister::SetMode;


RegisterAccessResult ZeroRegister::get() {
  return RegisterAccessResult(data_storage);
}


RegisterAccessResult ZeroRegister::set(const llvm::ArrayRef<uint8_t> data, SetMode mode) {
  assert(data.size() == data_storage.size() && "Setting wrong length data");

  return RegisterAccessResult(RegisterAccessStatus::RAS_WriteOk);
}

