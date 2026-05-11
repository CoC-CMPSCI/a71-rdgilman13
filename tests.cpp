#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// [T1]  makearray() — size and value constraints
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("T1a: makearray returns size between 10 and 20", "[T1]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);
    REQUIRE(cnt >= 10);
    REQUIRE(cnt <= 20);
}

TEST_CASE("T1b: makearray fills all elements with values 0-99", "[T1]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);
    for (int i = 0; i < cnt; i++) {
        INFO("Element index " << i << " value " << numbers[i] << " out of range");
        REQUIRE(numbers[i] >= 0);
        REQUIRE(numbers[i] <= 99);
    }
}

TEST_CASE("T1c: makearray called multiple times gives valid independent arrays", "[T1]")
{
    int a[SIZE], b[SIZE];
    int ca = makearray(a);
    int cb = makearray(b);
    // Each call must independently satisfy constraints
    REQUIRE(ca >= 10);
    REQUIRE(ca <= 20);
    REQUIRE(cb >= 10);
    REQUIRE(cb <= 20);
    for (int i = 0; i < ca; i++) {
        REQUIRE(a[i] >= 0);
        REQUIRE(a[i] <= 99);
    }
    for (int i = 0; i < cb; i++) {
        REQUIRE(b[i] >= 0);
        REQUIRE(b[i] <= 99);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// [T2]  bubble() — single pass behaviour (largest bubbles to end)
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("T2a: one bubble() pass moves max to last position", "[T2]")
{
    int numbers[] = {9, 3, 7, 1, 5};
    int cnt = 5;
    // max is 9; after one pass it must be at index 4
    bubble(numbers, cnt);
    REQUIRE(numbers[cnt - 1] == 9);
}

TEST_CASE("T2b: one bubble() pass on known array produces correct adjacent swaps", "[T2]")
{
    // {2, 3, 0, 5, 4} → one pass:
    //   2<3 ok  3>0 swap→{2,0,3,5,4}  3<5 ok  5>4 swap→{2,0,3,4,5}
    int numbers[] = {2, 3, 0, 5, 4};
    int cnt = 5;
    bubble(numbers, cnt);
    REQUIRE(numbers[0] == 2);
    REQUIRE(numbers[1] == 0);
    REQUIRE(numbers[2] == 3);
    REQUIRE(numbers[3] == 4);
    REQUIRE(numbers[4] == 5);
}

TEST_CASE("T2c: one bubble() pass on already-sorted array leaves it unchanged", "[T2]")
{
    int numbers[] = {1, 2, 3, 4, 5};
    int cnt = 5;
    bubble(numbers, cnt);
    REQUIRE(numbers[0] == 1);
    REQUIRE(numbers[1] == 2);
    REQUIRE(numbers[2] == 3);
    REQUIRE(numbers[3] == 4);
    REQUIRE(numbers[4] == 5);
}

TEST_CASE("T2d: one bubble() pass on reverse-sorted array — max lands at end", "[T2]")
{
    int numbers[] = {5, 4, 3, 2, 1};
    int cnt = 5;
    bubble(numbers, cnt);
    REQUIRE(numbers[cnt - 1] == 5);
}

TEST_CASE("T2e: one bubble() pass with two-element array swaps when left > right", "[T2]")
{
    int numbers[] = {8, 3};
    bubble(numbers, 2);
    REQUIRE(numbers[0] == 3);
    REQUIRE(numbers[1] == 8);
}

TEST_CASE("T2f: one bubble() pass with duplicate values — max still at end", "[T2]")
{
    int numbers[] = {5, 5, 3, 5, 2};
    int cnt = 5;
    bubble(numbers, cnt);
    REQUIRE(numbers[cnt - 1] == 5);
}

// ─────────────────────────────────────────────────────────────────────────────
// [T3]  bubble() called N-1 times — array fully sorted
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("T3a: calling bubble() cnt-1 times fully sorts known array", "[T3]")
{
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int cnt = 7;
    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);
    for (int i = 0; i < cnt - 1; i++) {
        INFO("At index " << i << ": " << numbers[i] << " > " << numbers[i+1]);
        REQUIRE(numbers[i] <= numbers[i + 1]);
    }
}

TEST_CASE("T3b: calling bubble() cnt-1 times fully sorts reverse-sorted array", "[T3]")
{
    int numbers[] = {99, 80, 60, 40, 20, 10, 5, 1};
    int cnt = 8;
    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);
    for (int i = 0; i < cnt - 1; i++) {
        REQUIRE(numbers[i] <= numbers[i + 1]);
    }
}

TEST_CASE("T3c: fully sorted result from makearray when bubble called cnt-1 times", "[T3]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);
    // find max before sorting
    int maxVal = numbers[0];
    for (int i = 1; i < cnt; i++)
        if (numbers[i] > maxVal) maxVal = numbers[i];

    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);

    // last element must be max
    REQUIRE(numbers[cnt - 1] == maxVal);
    // array must be non-decreasing
    for (int i = 0; i < cnt - 1; i++) {
        REQUIRE(numbers[i] <= numbers[i + 1]);
    }
}

TEST_CASE("T3d: array with all equal values stays sorted after repeated bubble passes", "[T3]")
{
    int numbers[] = {7, 7, 7, 7, 7};
    int cnt = 5;
    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);
    for (int i = 0; i < cnt; i++)
        REQUIRE(numbers[i] == 7);
}

// ─────────────────────────────────────────────────────────────────────────────
// [T4]  Integration — makearray + bubble (full sort) + value preservation
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("T4a: after full sort, min is at index 0 and max is at last index", "[T4]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);

    int minVal = numbers[0], maxVal = numbers[0];
    for (int i = 1; i < cnt; i++) {
        if (numbers[i] < minVal) minVal = numbers[i];
        if (numbers[i] > maxVal) maxVal = numbers[i];
    }

    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);

    REQUIRE(numbers[0] == minVal);
    REQUIRE(numbers[cnt - 1] == maxVal);
}

TEST_CASE("T4b: full sort preserves element count (no elements lost)", "[T4]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);

    // record sum before sorting
    long long sumBefore = 0;
    for (int i = 0; i < cnt; i++) sumBefore += numbers[i];

    for (int i = 0; i < cnt - 1; i++)
        bubble(numbers, cnt);

    // sum must be unchanged — no element may be created or destroyed
    long long sumAfter = 0;
    for (int i = 0; i < cnt; i++) sumAfter += numbers[i];

    REQUIRE(sumBefore == sumAfter);
}

TEST_CASE("T4c: single bubble pass on makearray output moves global max to last position", "[T4]")
{
    int numbers[SIZE];
    int cnt = makearray(numbers);

    int maxVal = numbers[0];
    for (int i = 1; i < cnt; i++)
        if (numbers[i] > maxVal) maxVal = numbers[i];

    bubble(numbers, cnt);

    REQUIRE(numbers[cnt - 1] == maxVal);
}

TEST_CASE("T4d: repeated bubble passes give non-decreasing array for any makearray output", "[T4]")
{
    // Run the full pipeline several times with fresh random arrays
    for (int run = 0; run < 5; run++) {
        int numbers[SIZE];
        int cnt = makearray(numbers);
        for (int i = 0; i < cnt - 1; i++)
            bubble(numbers, cnt);
        for (int i = 0; i < cnt - 1; i++) {
            INFO("run " << run << " index " << i);
            REQUIRE(numbers[i] <= numbers[i + 1]);
        }
    }
}
