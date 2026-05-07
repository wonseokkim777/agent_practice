# Gilded Rose Kata (C++)

The classic [Gilded Rose Kata](https://github.com/emilybache/GildedRose-Refactoring-Kata) implemented in C++ with Google Mock tests and Conjured item support.

## Requirements

- Visual Studio 2022 (MSVC 14.x)
- MSBuild
- NuGet (Google Test 1.11.0 — restored automatically via `packages/`)
- OpenCppCoverage (optional, for coverage)

## Build & Run

```powershell
# Build (Debug — compiles test executable)
msbuild GildedRose.sln /p:Configuration=Debug /p:Platform=x64

# Run tests
.\x64\Debug\GildedRose.exe

# Build (Release — compiles demo simulation)
msbuild GildedRose.sln /p:Configuration=Release /p:Platform=x64

# Run 30-day demo
.\x64\Release\GildedRose.exe
```

## Test Coverage

```powershell
OpenCppCoverage.exe --sources "C:\reviewer\GildedRose\*.cpp" --export_type=html:coverage -- .\x64\Debug\GildedRose.exe
# Report: .\coverage\index.html
```

## Item Rules

| Item | sellIn | Quality |
|------|--------|---------|
| Normal | −1/day | −1/day; −2/day after sell date; min 0 |
| Aged Brie | −1/day | +1/day; +2/day after sell date; max 50 |
| Backstage passes | −1/day | +1 normally; +2 when ≤10 days; +3 when ≤5 days; 0 after concert |
| Sulfuras | never | always 80, never mutated |
| Conjured | −1/day | −2/day; −4/day after sell date; min 0 |

## Architecture

```
GildedRose/
├── gilded_rose.h          # Item struct, GildedRose class declaration
├── gilded_rose.cpp        # updateQuality() — per-item-type methods
├── gilded_rose_test.cpp   # Google Mock tests (22 test cases)
└── main.cpp               # Debug: runs tests / Release: runs demo
```

`updateQuality()` dispatches to a private method per item type:

```
updateItem()
├── updateNormal()
├── updateAgedBrie()
├── updateBackstagePass()
├── updateConjured()
└── (Sulfuras: no-op)
```

Quality bounds (`[0, 50]`) are enforced by `increaseQuality()` / `decreaseQuality()` helpers.

## Test Cases (22)

| Suite | Count |
|-------|-------|
| NormalItemTest | 4 |
| AgedBrieTest | 4 |
| SulfurasTest | 2 |
| BackstagePassTest | 6 |
| ConjuredItemTest | 4 |
| QualityBoundsTest | 2 |

## Kata Constraints

- `Item` class must not be modified.
- `Sulfuras` quality is always 80 and is never altered by `updateQuality()`.
