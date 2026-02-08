#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* ------------------------------------------------------------
 * WHY HALVING LEADS TO O(log N)
 * ------------------------------------------------------------
 *
 * If you cut the problem in HALF each step:
 *
 * N
 * N/2
 * N/4
 * N/8  
 * ...
 * 1
 *
 * How many times can you divide by 2 until you reach 1?
 *
 * That number is log2(N).
 *
 * Example:
 * N = 1024
 * 1024 -> 512 -> 256 -> 128 -> 64 -> 32 -> 16 -> 8 -> 4 -> 2 -> 1
 * Steps = 10 = log2(1024)
 *
 * So the number of iterations grows VERY slowly even if N is large.
 * That is why O(log N) is excellent for embedded systems.
 *
 * ------------------------------------------------------------
 */


/* ============================================================
 * BINARY SEARCH — O(log N)
 * ============================================================
 *
 * Requirements:
 * - Array must be SORTED
 * - Works on fixed-size buffers
 * - No recursion (safe for small stacks)
 *
 * Embedded Tip:
 * Never calculate mid like this:
 *     mid = (low + high) / 2;
 *
 * Because on small CPUs (16-bit), low + high may overflow.
 *
 * Safe formula:
 *     mid = low + (high - low) / 2;
 *
 * This never overflows.
 *
 * ------------------------------------------------------------
 */


 int binary_search(const int *arr, const size_t N, int target)
{
    size_t LOW = 0; 
    size_t HIGHT = N - 1; 
    size_t mid; 
    int result = -1;

    if (arr == NULL || N == 0)
    {
        return result;  /* Invalid input */
    }

    while(LOW <= HIGHT)
    {
        mid = LOW + (HIGHT - LOW) / 2;

        if (arr[mid] == target)
        {
            result = (int)mid;  /* Target found */
            break;
        }
        else if (arr[mid] < target)
        {
            LOW = mid + 1;  /* Search in the right half */
        }
        else
        {
            if (mid == 0)
            {
                break;  /* Prevent underflow */
            }

            HIGHT = mid - 1;  /* Search in the left half */
        }
    }

    return result;
}


int main()
{
    int data[] = {2, 3, 4, 10, 40, 50, 60, 70, 80, 90};
    size_t size = sizeof(data) / sizeof(data[0]);
    int target = 22;

    int result = binary_search(data, size, target);
    if (result != -1)
    {
        // Target found
        printf("Element found at index %d\n", result);
    }
    else
    {
        // Target not found
        printf("Element not found in array\n");
    }

    return 0;
}