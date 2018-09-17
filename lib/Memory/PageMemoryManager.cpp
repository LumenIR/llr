#include "llr/Memory/PageMemoryManager.h"

#include "llr/Memory/MemoryAccessResult.h"
#include "llr/Memory/MemoryAddress.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_os_ostream.h"

#include <algorithm>
#include <cassert>
#include <cstdint>

using namespace llr;
using namespace llvm;

using MAS = enum MemoryAccessStatus;

constexpr size_t PAGE_SIZE_POWER_2 = 16;

PageMemoryManager::PageMemoryManager() :
  PageSize(1 << PAGE_SIZE_POWER_2),
  begin_addr(0x0L),
  end_addr(0xFFFFL)
{
//TODO assert if size is not power of 2

}



/*
 *
 *
 *  |0                      |1                      |n                      |n+m                    |
 *  |                       |                       |                       |                       |
 *                                                              ^ - Address                 ^
 *                                                              |     Data.size             |
 *                                                  | PageOffset|
 *
*/


MemoryAccessResult PageMemoryManager::write(const MemoryAddress &Addr, const ArrayRef<uint8_t> &d) {
  //TODO 65kb page by default
  const uint64_t first_page_idx     = ((uint64_t)Addr & 0xFFFFFFFFFFFF0000L) >> 16;
  const uint64_t first_page_offset  = ((uint64_t)Addr & 0x000000000000FFFFL);


  uint64_t data_remains = d.size();
  uint64_t curr_page_idx          = first_page_idx;
  uint64_t curr_page_begin_offset = first_page_offset;

  uint64_t curr_page_end_offset;

  do {
    if (PageSize - curr_page_begin_offset > data_remains) {
      //feets in current page
      curr_page_end_offset = curr_page_begin_offset + data_remains;
    } else {
      //need more pages
      curr_page_end_offset = PageSize;
    }
    const uint64_t curr_write_size = curr_page_end_offset - curr_page_begin_offset;

    const auto& it = pages.find(curr_page_idx);

    MemoryPage *page;
    if (it != pages.end()) {
      page = it->second.get();
    } else {
      page = new MemoryPage();
      page->isValid = true;
      page->data.resize(PageSize);
      std::fill(page->data.begin(), page->data.end(), 0xDEADBEAF);

      MemoryPage_uptr newPage = MemoryPage_uptr(page);
      pages.emplace(curr_page_idx, std::move(newPage));
    }
    std::copy(
          d.begin() + d.size() - data_remains,
          d.begin() + d.size() - data_remains + curr_write_size,
          page->data.begin() + curr_page_begin_offset
    );


    data_remains -= curr_write_size;
    // move to the next page
    curr_page_idx++;
    // writing to the next page from the beginning
    curr_page_begin_offset = 0;
  }  while (data_remains > 0);

  return {MAS::WriteOK, d, Addr};
}

MemoryAccessResult PageMemoryManager::read(const MemoryAddress &Addr, size_t size) {
  std::vector<uint8_t> result_data(size);

  const uint64_t first_page_idx     = ((uint64_t)Addr & 0xFFFFFFFFFFFF0000L) >> 16;
  const uint64_t first_page_offset  = ((uint64_t)Addr & 0x000000000000FFFFL);

  uint64_t data_remains = size;
  uint64_t curr_page_idx          = first_page_idx;
  uint64_t curr_page_begin_offset = first_page_offset;

  uint64_t curr_page_end_offset;

  do {
    if (PageSize - curr_page_begin_offset > data_remains) {
      //feets in current page
      curr_page_end_offset = curr_page_begin_offset + data_remains;
    } else {
      //need more pages
      curr_page_end_offset = PageSize;
    }
    const uint64_t curr_read_size = curr_page_end_offset - curr_page_begin_offset;

    const auto& it = pages.find(curr_page_idx);

    MemoryPage *page;
    if (it != pages.end()) {
      page = it->second.get();
    } else {
      return {MAS::NotFound, Addr};
    }
    std::copy(
          page->data.begin() + curr_page_begin_offset,
          page->data.begin() + curr_page_end_offset,
          result_data.begin() + size - data_remains
    );


    data_remains -= curr_read_size;
    // move to the next page
    curr_page_idx++;
    // writing to the next page from the beginning
    curr_page_begin_offset = 0;
  }  while (data_remains > 0);

  return MemoryAccessResult{MAS::ReadOK, result_data, Addr};
}

const MemoryAddress PageMemoryManager::begin_address() const {
  return begin_addr;
}

const MemoryAddress PageMemoryManager::end_address() const {
  return end_addr;
}
