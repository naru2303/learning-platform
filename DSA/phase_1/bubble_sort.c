/*
Why this is O(N²)
	•	Outer loop runs ~N times
	•	Inner loop runs ~N times (slightly less each pass, but still proportional to N)
	•	Total comparisons ≈ N × N / 2 → O(N²)

Embedded Notes
	•	Works on static arrays (no heap).
	•	Deterministic execution time for fixed N.
	•	Do not use for large buffers or inside ISRs.
	•	Good only for:
	•	very small arrays
	•	nearly sorted data
*/

#include <stdio.h>
#include <stddef.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort (int *arr, size_t N)
{
    for (size_t i = 0; i < N - 1 ; ++i)
    {
        for (size_t j = 0; j < N - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                // swap arr[j] and arr[j+1]
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }

    return;
}

int main(void)
{
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size = sizeof(data)/sizeof(data[0]);

    bubble_sort(data, size);

    printf("Sorted array: \n");
    for (size_t i = 0; i < size; i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}