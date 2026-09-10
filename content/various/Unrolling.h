/**
 * Description: Calls f(i) for i in [l, r), four iterations at a time.
 * Status: tested
 */
#pragma once

template<class F> void unroll4(int l, int r, F f){
  while((l&3) and l<r) f(l++);
  for(;l+4<=r;l+=4) f(l), f(l+1), f(l+2), f(l+3);
  while(l<r) f(l++);
}
