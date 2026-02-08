#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* ============================================================
 * 2) EUCLID'S ALGORITHM (GCD) — O(log N)
 * ============================================================
 *
 * Finds the Greatest Common Divisor of two numbers.
 *
 * Idea:
 * gcd(a, b) = gcd(b, a % b)
 * until b becomes 0.
 *
 * Example:
 * gcd(48, 18)
 * -> gcd(18, 12)
 * -> gcd(12, 6)
 * -> gcd(6, 0)
 * result = 6
 *
 * Why O(log N)?
 * Because the remainder shrinks fast — similar to halving.
 *
 * ------------------------------------------------------------
 */
uint32_t gcd_euclid(uint32_t a, uint32_t b)
{
    while (b != 0)
    {
        uint32_t r = a % b;
        a = b;
        b = r;

        /*
            * Numbers decrease quickly.
            * Worst case still grows logarithmically.
            */
    }

    return a;
}

int main(void)
{
    uint32_t a = 48;
    uint32_t b = 18;
    uint32_t result = gcd_euclid(a, b);

    printf("GCD of %u and %u is %u\n", a, b, result);

    return 0;
}