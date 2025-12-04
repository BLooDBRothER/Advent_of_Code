# Day 2 - Part 1 Invalid ID Detection Algorithm

## Problem Statement

Given ranges of IDs, find all "invalid IDs" where an invalid ID is a number consisting of a digit sequence repeated exactly twice.

**Examples of Invalid IDs:**
- `11` = "1" repeated twice
- `1010` = "10" repeated twice  
- `123123` = "123" repeated twice
- `99` = "9" repeated twice

**Valid IDs (not invalid):**
- `101` (cannot be split into two equal parts)
- `1234` (first half "12" ≠ second half "34")
- `0101` (has leading zero, not a valid number)

**Task:** For each range `[start, end]`, find all invalid IDs and sum them.

## Algorithm Overview

### Key Insight

**Only even-length numbers can be invalid IDs** because they must be split into two equal halves for comparison.

The algorithm organizes the search by **digit length** rather than checking each number individually.

### Algorithm Steps

```
For each digit length d in [start_digit, end_digit]:
    
    1. Skip if d is odd (cannot be split evenly)
    
    2. Determine the numeric sub-range for digit length d:
       - If d == start_digit and d == end_digit: use [start, end]
       - If d == start_digit: use [start, 10^d - 1]
       - If d == end_digit: use [10^(d-1), end]
       - Otherwise: use [10^(d-1), 10^d - 1]
    
    3. Extract pattern boundaries:
       - Split sub-range boundaries in half
       - Determine valid pattern range [pattern_start, pattern_end]
    
    4. Generate invalid IDs:
       - For each pattern p in [pattern_start, pattern_end]:
         - Invalid ID = concatenate(p, p)
         - Example: pattern=12 → "12" + "12" = 1212
```

## Detailed Example

### Example 1: Range [4, 15]

```
Input: [4, 15]

Step 1: Identify digit lengths
- start_digit = len("4") = 1
- end_digit = len("15") = 2

Step 2: Process each digit length

Digit length 1:
  → SKIP (odd length)

Digit length 2:
  → Sub-range: [10, 15] (all 2-digit numbers in range)
  
  → Split boundaries:
     Start "10" → first_half=1, second_half=0
     End "15"   → first_half=1, second_half=5
  
  → Determine pattern range:
     include_start: 1 >= 0 → True (pattern 1 is valid)
     include_end: 1 <= 5 → True (pattern 1 is valid)
     Pattern range: [1, 1]
  
  → Generate invalid IDs:
     pattern=1 → "1" + "1" = 11

Result: [11]
Sum: 11
```

### Example 2: Range [95, 115]

```
Input: [95, 115]

Step 1: Identify digit lengths
- start_digit = 2
- end_digit = 3

Step 2: Process each digit length

Digit length 2:
  → Sub-range: [95, 99] (all 2-digit numbers in original range)
  
  → Split boundaries:
     Start "95" → first_half=9, second_half=5
     End "99"   → first_half=9, second_half=9
  
  → Determine pattern range:
     include_start: 9 >= 5 → True
     include_end: 9 <= 9 → True
     Pattern range: [9, 9]
  
  → Generate invalid IDs:
     pattern=9 → "9" + "9" = 99

Digit length 3:
  → SKIP (odd length)

Result: [99]
Sum: 99
```

### Example 3: Range [998, 1012]

```
Input: [998, 1012]

Step 1: Identify digit lengths
- start_digit = 3
- end_digit = 4

Step 2: Process each digit length

Digit length 3:
  → SKIP (odd length)

Digit length 4:
  → Sub-range: [1000, 1012] (all 4-digit numbers in original range)
  
  → Split boundaries:
     Start "1000" → first_half=10, second_half=0
     End "1012"   → first_half=10, second_half=12
  
  → Determine pattern range:
     include_start: 10 >= 0 → True
     include_end: 10 <= 12 → True
     Pattern range: [10, 10]
  
  → Generate invalid IDs:
     pattern=10 → "10" + "10" = 1010

Result: [1010]
Sum: 1010
```

### Example 4: Range [11, 22]

```
Input: [11, 22]

Step 1: Identify digit lengths
- start_digit = 2
- end_digit = 2

Step 2: Process digit length 2

Digit length 2:
  → Sub-range: [11, 22] (same as input)
  
  → Split boundaries:
     Start "11" → first_half=1, second_half=1
     End "22"   → first_half=2, second_half=2
  
  → Determine pattern range:
     include_start: 1 >= 1 → True
     include_end: 2 <= 2 → True
     Pattern range: [1, 2]
  
  → Generate invalid IDs:
     pattern=1 → "1" + "1" = 11
     pattern=2 → "2" + "2" = 22

Result: [11, 22]
Sum: 33
```

## Boundary Logic

The `include_number()` function determines whether to include the boundary pattern:

```cpp
bool include_number(string number, bool is_start) {
    int64_t first_half = stoll(number.substr(0, number.length()/2));
    int64_t second_half = stoll(number.substr(number.length()/2));
    return is_start ? first_half >= second_half : first_half <= second_half;
}
```

**For START boundary:**
- If `first_half >= second_half`: Include this pattern
  - The smallest invalid ID with this pattern is within range
- Otherwise: Start from next pattern

**For END boundary:**
- If `first_half <= second_half`: Include this pattern
  - The largest invalid ID with this pattern is within range
- Otherwise: End at previous pattern

**Example:**
```
Range [95, 99]:
  Start "95" → (9, 5): 9 >= 5 → True, include pattern 9
  End "99"   → (9, 9): 9 <= 9 → True, include pattern 9
  Result: pattern=9 generates 99 ✓

Range [96, 98]:
  Start "96" → (9, 6): 9 >= 6 → True, include pattern 9
  End "98"   → (9, 8): 9 <= 8 → False, exclude pattern 9
  Result: No patterns (9 would generate 99, which is > 98)
```

## Time Complexity Analysis

### Complexity Breakdown

**Outer Loop:**
- Iterates through digit lengths: `O(end_digit - start_digit + 1)`
- Half of these are skipped (odd lengths)
- Effective iterations: `O((end_digit - start_digit + 1) / 2)`

**Inner Loop (per digit length):**
- Iterates through patterns for that digit length
- Number of patterns ≈ `O(10^(d/2))` where d is the digit length
- Only generates valid invalid IDs (no wasted iterations)

**Total Complexity:**
```
O(Σ patterns_per_digit_length) = O(total_invalid_ids)
```

### Complexity Examples

**Range [1, 10,000]:**
- Digit lengths: 2, 4 (skip 1, 3, 5)
- Patterns:
  - digit=2: 9 patterns (1-9)
  - digit=4: 90 patterns (10-99)
- Total: 99 iterations
- Result: 99 invalid IDs

**Range [1, 1,000,000]:**
- Digit lengths: 2, 4, 6
- Patterns:
  - digit=2: 9 patterns
  - digit=4: 90 patterns
  - digit=6: 900 patterns
- Total: 999 iterations
- Result: 999 invalid IDs

**Range [1,000,000,000, 1,000,100,000]:**
- Digit lengths: 10 only
- Patterns: 1 pattern (only one 10-digit invalid ID in this range)
- Total: 1 iteration
- Result: 1 invalid ID

### Efficiency Metrics

**Key advantages:**
1. **100% iteration efficiency:** Every iteration produces a valid invalid ID
2. **Minimal outer loop:** Only processes digit lengths that exist in range
3. **No validation overhead:** Patterns are correct by construction
4. **Direct calculation:** Pattern boundaries computed mathematically

**Comparison to brute force:**
```
Brute Force: O(n) where n = end - start
This Algorithm: O(sqrt(n)) approximately

Example [1, 1,000,000]:
- Brute force: 1,000,000 checks
- This algorithm: 999 iterations
- Speedup: ~1000x
```

## Space Complexity

- **Auxiliary Space:** O(1)
  - Only stores current pattern and generated invalid ID
  - No large data structures needed

- **Output Space:** O(k) where k = number of invalid IDs
  - Must store all found invalid IDs

## Algorithm Properties

### Correctness

**Guarantee:** Finds ALL invalid IDs in the range because:
1. Processes every even digit length in [start_digit, end_digit]
2. For each digit length, calculates exact pattern boundaries
3. Generates all possible invalid IDs from those patterns
4. Boundary logic ensures no invalid IDs are missed or duplicated

### Optimality

**This algorithm is optimal because:**
1. Must examine every invalid ID at least once (output requirement)
2. Algorithm examines each invalid ID exactly once
3. No wasted iterations on non-invalid IDs
4. Direct computation of pattern boundaries (no search needed)

## Pseudocode

```
function find_invalid_ids(start, end):
    result = []
    start_digit = count_digits(start)
    end_digit = count_digits(end)
    
    for digit in [start_digit..end_digit]:
        if digit is odd:
            continue
        
        // Determine sub-range for this digit length
        if start_digit == end_digit:
            sub_start = start
            sub_end = end
        else if digit == start_digit:
            sub_start = start
            sub_end = 10^digit - 1
        else if digit == end_digit:
            sub_start = 10^(digit-1)
            sub_end = end
        else:
            sub_start = 10^(digit-1)
            sub_end = 10^digit - 1
        
        // Calculate pattern boundaries
        half_len = digit / 2
        start_pattern = first_half(sub_start, half_len)
        end_pattern = first_half(sub_end, half_len)
        
        // Adjust boundaries based on second half
        if not include_start(sub_start):
            start_pattern += 1
        if not include_end(sub_end):
            end_pattern -= 1
        
        // Generate invalid IDs
        for pattern in [start_pattern..end_pattern]:
            invalid_id = concatenate(pattern, pattern)
            result.append(invalid_id)
    
    return result
```

## Implementation Notes

1. **String concatenation:** Pattern + pattern efficiently generates invalid IDs
2. **Integer boundaries:** All comparisons use integer arithmetic (fast)
3. **No floating-point math:** Avoids precision issues
4. **Single pass:** Each invalid ID generated exactly once

## Summary

This algorithm efficiently finds invalid IDs by:
- ✅ Organizing search by digit length
- ✅ Skipping impossible cases (odd lengths)
- ✅ Direct pattern boundary calculation
- ✅ Zero validation overhead
- ✅ 100% iteration efficiency

**Time Complexity:** O(total_invalid_ids)  
**Space Complexity:** O(1) auxiliary, O(k) output  
**Efficiency:** Optimal for this problem