# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Test Commands

This is a Visual Studio C++ project (MSBuild). Open `GildedRose.sln` in Visual Studio, or use MSBuild from the command line:

```powershell
# Build Debug (compiles tests)
msbuild GildedRose.sln /p:Configuration=Debug /p:Platform=x64

# Build Release (compiles demo runner)
msbuild GildedRose.sln /p:Configuration=Release /p:Platform=x64

# Run tests (Debug build produces the test executable)
.\x64\Debug\GildedRose.exe

# Run demo simulation (Release build)
.\x64\Release\GildedRose.exe
```

Test framework: **Google Test / Google Mock 1.11.0** (via NuGet, located in `packages/`).

```powershell
# Measure test coverage (requires OpenCppCoverage in PATH)
OpenCppCoverage.exe --sources C:\*.cpp --export_type=html:coverage -- .\x64\Debug\GildedRose.exe
```

Coverage results are written as HTML to the `.\coverage\` directory.

## Architecture

This is the classic **Gilded Rose Kata** — a refactoring exercise. The core is intentionally a single method with deeply nested conditionals.

### Key files

- `GildedRose/gilded_rose.h` — `Item` struct (name, sellIn, quality) and `GildedRose` class declaration
- `GildedRose/gilded_rose.cpp` — `GildedRose::updateQuality()`, the monolithic method with all item rules
- `GildedRose/gilded_rose_test.cpp` — Google Test test cases (currently a single placeholder)
- `GildedRose/main.cpp` — dual-purpose entry point: **Debug builds** run the test suite via `RUN_ALL_TESTS()`; **Release builds** run a 30-day demo simulation

### Item update rules (encoded in `updateQuality()`)

| Item | sellIn | Quality behavior |
|------|--------|-----------------|
| Normal item | −1/day | −1/day; −2/day after sell date |
| Aged Brie | −1/day | +1/day; +2/day after sell date; max 50 |
| Backstage passes | −1/day | +1 normally; +2 when ≤10 days; +3 when ≤5 days; 0 after concert |
| Sulfuras | never changes | always 80, never mutated |

Quality is bounded to [0, 50] for all items except Sulfuras (fixed at 80). Item type is identified by exact string comparison — there is no type enum or polymorphism.

### Kata constraints

- The `Item` class **must not be modified** (kata rule).
- `Sulfuras` quality is always 80 and is never altered by `updateQuality()`.
- A `Conjured` item category (degrades 2× as fast as normal) is the typical extension task.
