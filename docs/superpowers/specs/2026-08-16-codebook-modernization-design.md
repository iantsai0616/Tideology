# Tideology codebook modernization design

## Context

Tideology is a competitive-programming codebook intended to be copied by
hand from a printed PDF during contests. The current source mixes upstream
KACTL code, team additions, several coding styles, implicit dependencies,
and implementations with different performance and testing levels.

The initial baseline found that the existing compile script passes 83 of 131
headers. This number is not itself the bug count: some failures are genuine,
while many geometry snippets intentionally require shared geometry types that
the current test does not include. Confirmed problems include the broken
`pii` macro, duplicated `pb`, conflicts caused by `#define int long long`, an
NTT header with two definitions of `mod`, and `Operation.h` referring to an
`NTT<MAXN, RT>` type that does not exist in the current NTT header.

## Goals

- Make every codebook entry reliable in its documented copy context.
- Prefer implementations that are easier to type and remember by hand.
- Replace an implementation when an equivalent version is easier to copy.
- Never accept a replacement that is slower in the intended use case.
- Replace implementations that are already unnecessarily slow, beginning
  with NTT.
- Match the owner's contest style without copying accidental mistakes from
  the example solution.
- Keep dependencies short and explicit instead of duplicating shared code.
- Produce an exact, per-file record of every source change.
- Defer PDF selection and layout until the source library is stable; the
  eventual PDF has a hard limit of 25 total pages.

## Non-goals

- No PDF inclusion decisions during the source-modernization phase.
- No architecture- or CPU-specific implementation that only performs well on
  one of ARM64 or x86-64.
- No general-purpose abstraction added merely for elegance.
- No unrelated repository cleanup.

## Source and style contract

The target is portable GNU++20 compiled with `-O2`. The base template keeps
the owner's short aliases and macros, including `#define int long long`, but
removes duplicate or broken definitions and isolates code that truly requires
32-bit integers. It uses two-space indentation, braces and control-flow
formatting matching the supplied contest solution, short conventional names,
and `and`/`or` where that improves typing consistency.

Copyability takes priority over genericity. Short direct loops are preferred
to layers of traits or callbacks. Public names, indexing conventions, and
usage may change when the replacement is materially easier to copy, provided
the header documents the new contract concisely.

## Dependency model

An entry need not compile with only `template.cpp` when that would duplicate a
substantial prerequisite. Such an entry instead carries a compact `Requires:`
line naming codebook prerequisites such as `GeometryTemplate` or `NTT`.

The compile harness will resolve those declared prerequisites and compile the
same combined source a contestant is expected to copy. Missing, cyclic, stale,
or unnecessary dependencies are failures. Headers with configurable constants
such as `N`, `M`, or a modulus must state or supply the smallest compile fixture
needed by the test.

## Audit and change workflow

1. Inventory every codebook header and classify it as working, broken,
   dependency-bound, hard to copy, slow, or a combination of these.
2. Before changing any repository content, create
   `docs/codebook-change-log.md`. It will list every planned file with:
   path, observed issue, proposed change, reason, and required verification.
   The ledger includes its own row and all tooling or documentation changes,
   not only algorithm headers.
3. Repair the base template and make the audit harness use GNU++20 and the
   documented dependency model.
4. Review the codebook category by category: contest utilities, data
   structures, strings, number theory, numerical algorithms, graphs, geometry,
   combinatorics, and miscellaneous algorithms.
5. For a confirmed defect, first add the smallest reproducible compile,
   regression, or differential test, then fix the root cause.
6. For a replacement, compare it with the current version on correctness,
   complexity, source length, copy hazards, and measured performance. Keep the
   replacement only if it is no slower for representative workloads.
7. Update the per-file ledger at the same time as each approved file change.
   No content file may be modified without a matching ledger row.
8. Finish by comparing the ledger with `git diff --name-only` and describe
   every modified file in the handoff.

## NTT performance work

The current NTT is both awkward to consume and a stated performance concern.
The replacement will:

- expose one coherent modulus/root contract without conflicting includes;
- work correctly with the base template's `int` macro;
- retain O(N log N) complexity and portable scalar GNU++20 code;
- support the polynomial operations that currently expect
  `NTT<MAXN, RT>`, or update those operations and their documented dependency
  as one tested unit;
- pass naive-convolution differential tests and boundary-size tests; and
- beat or match the old implementation's median `-O2` time at several powers
  of two after warm-up. The existing ARM64 baseline for multiplying two
  length-2^20 polynomials is approximately 269-274 ms and will be retained as
  comparative evidence, not as a cross-machine absolute target.

## Verification

Verification is layered rather than relying on a single compile count:

- compile the base template in debug and submission modes;
- compile every entry with its resolved prerequisites under GNU++20;
- run all existing stress tests after making their fixtures match the real
  copy context;
- add regression tests for every confirmed bug;
- add randomized differential tests for replacement implementations where a
  simple oracle is practical;
- benchmark performance-sensitive replacements with identical compiler flags,
  inputs, process conditions, and repeated median timings;
- compare source line and non-whitespace character counts for every
  replacement and for the whole library; and
- inspect the final Git diff against the per-file change ledger.

A warning may remain only when it is understood, harmless in the intended
copy context, and documented in the ledger. An untested replacement, a missing
dependency, a performance regression, or an unlisted modified file blocks
completion.

## Later PDF phase

After the source work is reviewed, PDF inclusion is a separate decision. The
selected material will be built, rendered, and visually inspected under the
25-page hard limit. Source files are not shortened by sacrificing correctness
merely to force an entry into the PDF; selection and layout resolve the final
page budget.
