/**
 * Copyright (c) 2017-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include "util.h"

#include <memory>

// Tracks which ranges of memory have been consumed during parsing,
// so that we can easily identify sections that may have data we don't
// yet understand.
class MemoryAccounter {
 public:
  MemoryAccounter() = default;
  UNCOPYABLE(MemoryAccounter);
  virtual ~MemoryAccounter();

  static std::unique_ptr<MemoryAccounter> New(ConstBuffer buf);

  // Print a report of any memory in buf_ that has either never
  // been consumed, or has been consumed more than once.
  virtual void print() = 0;

  // Accounting functions - use these to mark portions of the tracked
  // buffer consumed.

  // memcpy range from the tracked buffer, and mark the copied range
  // as consumed.
  virtual void memcpyAndMark(void* dest, const char* src, size_t count) = 0;

  // Manually mark ranges of the buffer consumed.
  virtual void markRangeConsumed(uint32_t begin, uint32_t count) = 0;
  virtual void markRangeConsumed(const char* ptr, uint32_t count) = 0;
  virtual void markBufferConsumed(ConstBuffer subBuffer) = 0;
};
