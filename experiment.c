#include <stdio.h>
#include <stdint.h>

#define SIGN_BITS 1
#define EXPONENT_BITS 11
#define MANTISSA_BITS 52
#define EXPONENT_BIAS 1023

uint64_t to_bits(double a) {
    union {
        double f;
        uint64_t u;
    } fu = { .f = a };
    return fu.u;
}

int main()
{
    uint64_t b = to_bits(a);
    printf("b : %llX | %lld\n", b, b);

    uint64_t s_pre = b >> (64 - SIGN_BITS);
    uint64_t e_pre = (b << SIGN_BITS) >> (64 - EXPONENT_BITS);
    uint64_t m_pre = (b << (SIGN_BITS + EXPONENT_BITS)) >> (64 - MANTISSA_BITS);
    m_pre += ((uint64_t) 1) << MANTISSA_BITS;
    printf("s_pre: %llX | %lld\n", s_pre, s_pre);
    printf("e_pre: %llX | %lld\n", e_pre, e_pre);
    printf("m_pre: %llX | %lld\n", m_pre, m_pre);


    int64_t m = ((s_pre == 1) ? -1 : 1) * (int64_t) (m_pre);
    int64_t e = ((int64_t) e_pre) - EXPONENT_BIAS - MANTISSA_BITS;
    while (m % 2 == 0) {
        m /= 2;
        e += 1;
    }

    printf("m : %lld\n", m);
    printf("e : %lld\n", e);

}
