/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 * "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Status: tested
 */
#pragma once

// Either globally or in a single class:
alignas(max_align_t) static char buf[450 << 20];
static size_t bumpPos = sizeof buf;
void* operator new(size_t s){
  assert(s <= bumpPos);
  bumpPos = (bumpPos-s) & ~(alignof(max_align_t)-1);
  return (void*)&buf[bumpPos];
}
void operator delete(void*) noexcept {}
void operator delete(void*, size_t) noexcept {}
size_t bumpMark(){ return bumpPos; }
void bumpReset(size_t p){ assert(bumpPos <= p && p <= sizeof buf); bumpPos = p; }
