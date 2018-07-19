//===- llr/unittest/Memory/SimpleMemoryManagerTests.cpp --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llr/Memory/MemoryBlock.h"
#include "llr/Memory/SimpleMemory.h"
#include "llr/Memory/MemoryAccessResult.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "gtest/gtest.h"

#include <vector>
#include <cstdint>
#include <memory>


using namespace llvm;
using namespace llr;


struct MemoryAcc {
  MemoryAddress addr;
  ArrayRef<uint8_t> data;
};


static const uint8_t DATA_T[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
  17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64
};

static const uint8_t* DATA = DATA_T;

TEST(MemoryBlock, readAfterWrite) {

  std::vector<struct MemoryAcc> accesses = {
    {{0x00000000}, {DATA, (size_t)1}},
    {{0x00000000}, {DATA, (size_t)2}},
    {{0x00000000}, {DATA, (size_t)4}},
    {{0x00000000}, {DATA, (size_t)8}},
    {{0x00000000}, {DATA, (size_t)32}},
    {{0x00000000}, {DATA, (size_t)64}},

    {{        63}, {DATA, (size_t)1}},
    {{        32}, {DATA, (size_t)32}},
  };

  Memory* memory = new MemoryBlock(0x0, 64);

  for(const auto& Acc : accesses) {
    MemoryAccessResult writeRes = memory->write(Acc.addr, Acc.data);
    EXPECT_EQ(writeRes.getStatus(), MemoryAccessStatus::WriteOK);
//    EXPECT_EQ(writeRes.getData().size(), Acc.data.size());


    MemoryAccessResult readRes = memory->read(Acc.addr, Acc.data.size());
    EXPECT_EQ(readRes.getData().size(), Acc.data.size());
    EXPECT_EQ(readRes.getStatus(), MemoryAccessStatus::ReadOK);

    EXPECT_EQ(memcmp(Acc.data.data(), readRes.getData().data(), Acc.data.size()), 0) << "Addr: " << Acc.addr << " Size: " << Acc.data.size();
  }
  delete memory;

  /////////// With offset ////////////////////////////////

  accesses = {
    {{  64}, {DATA, (size_t)1}},
    {{  64}, {DATA, (size_t)2}},
    {{  64}, {DATA, (size_t)4}},
    {{  64}, {DATA, (size_t)8}},
    {{  64}, {DATA, (size_t)32}},
    {{  64}, {DATA, (size_t)64}},

    {{ 127}, {DATA, (size_t)1}},
    {{  96}, {DATA, (size_t)32}},
  };

  memory = new MemoryBlock(64, 128);

  for(const auto& Acc : accesses) {
    MemoryAccessResult writeRes = memory->write(Acc.addr, Acc.data);
    EXPECT_EQ(writeRes.getStatus(), MemoryAccessStatus::WriteOK);
//    EXPECT_EQ(writeRes.getData().size(), Acc.data.size());


    MemoryAccessResult readRes = memory->read(Acc.addr, Acc.data.size());
    EXPECT_EQ(readRes.getData().size(), Acc.data.size());
    EXPECT_EQ(readRes.getStatus(), MemoryAccessStatus::ReadOK);

    EXPECT_EQ(memcmp(Acc.data.data(), readRes.getData().data(), Acc.data.size()), 0) << "Addr: " << Acc.addr << " Size: " << Acc.data.size();
  }
  delete memory;
}


TEST(SimpleMemoryManager, readAfterWrite) {

  std::vector<struct MemoryAcc> accesses = {
    {{0x00000000}, {DATA, (size_t)1}},
    {{0x00000000}, {DATA, (size_t)2}},
    {{0x00000000}, {DATA, (size_t)4}},
    {{0x00000000}, {DATA, (size_t)8}},
    {{0x00000000}, {DATA, (size_t)16}},
    {{0x00000000}, {DATA, (size_t)32}},
    {{0x00000000}, {DATA, (size_t)64}}
  };

  Memory* memory = new SimpleMemoryManager();

  for(const auto& Acc : accesses) {
    MemoryAccessResult writeRes = memory->write(Acc.addr, Acc.data);
    EXPECT_EQ(writeRes.getStatus(), MemoryAccessStatus::WriteOK);
//    EXPECT_EQ(writeRes.getData().size(), Acc.data.size());


    MemoryAccessResult readRes = memory->read(Acc.addr, Acc.data.size());
    EXPECT_EQ(readRes.getData().size(), Acc.data.size());
    EXPECT_EQ(readRes.getStatus(), MemoryAccessStatus::ReadOK);

    EXPECT_EQ(memcmp(Acc.data.data(), readRes.getData().data(), Acc.data.size()), 0);
  }
}



