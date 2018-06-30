#include "llr/Registers/SimpleRegister.h"
#include "llr/Registers/RegisterAccessResult.h"

#include <cassert>
#include <cstdint>
#include <algorithm>

using namespace llvm;
using namespace llr;

using SetMode = llr::LLRRegister::SetMode;


RegisterAccessResult SimpleRegister::get() {
  return RegisterAccessResult(data_storage);
}


RegisterAccessResult SimpleRegister::set(const llvm::ArrayRef<uint8_t> data, SetMode mode) {
  assert(data.size() == data_storage.size() && "Setting wrong length data");
  assert(mode == SetMode::EXACT && "Only EXACT set supported");


  std::copy(data.begin(), data.end(), data_storage.begin());
  return RegisterAccessResult(RegisterAccessStatus::RAS_WriteOk);
}

