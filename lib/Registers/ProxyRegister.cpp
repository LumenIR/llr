#include "llr/Registers/ProxyRegister.h"
#include "llr/Registers/RegisterAccessResult.h"

#include <cassert>
#include <cstdint>
#include <algorithm>

using namespace llvm;
using namespace llr;

using SetMode = llr::LLRRegister::SetMode;


RegisterAccessResult ProxyRegister::get() {

  return RegisterAccessResult(ArrayRef<uint8_t>(data_ptr, RegisterSize));
}


RegisterAccessResult ProxyRegister::set(const llvm::ArrayRef<uint8_t> data, SetMode mode) {
  assert(data.size() == RegisterSize && "Setting wrong length data");
  assert(mode == SetMode::EXACT && "Only EXACT set supported");


  std::copy(data.begin(), data.end(), data_ptr);
  return RegisterAccessResult(RegisterAccessStatus::RAS_WriteOk);
}

