#ifndef QRTC_RNG_HPP
#define QRTC_RNG_HPP

#include "qrtc_internal.hpp"

namespace qrtc_internal
{

struct RNG
{
    uint64_t state[4] = {0, 0, 0, 0};

    // ---------------- Constructors ----------------

    RNG(uint64_t seed = 7564231ULL)
    {
        seed_rng(seed);
    }

    // ---------------- Core SFC64 ----------------

    static inline uint64_t rotl64(uint64_t x, int k)
    {
        return (x << k) | (x >> (64 - k));
    }

    inline uint64_t next_u64()
    {
        uint64_t out = state[1] + state[2] + state[0];

        state[0] = state[0] + 1;
        state[1] = state[2] ^ (state[2] >> 11);
        state[2] = state[3] + (state[3] << 3);
        state[3] = rotl64(state[3], 24) + out;

        return out;
    }

    // ---------------- Seeding ----------------

    inline void seed_rng(uint64_t seed)
    {
        state[0] = 1;
        state[1] = seed;
        state[2] = seed;
        state[3] = seed;

        // Warmup
        for (int i = 0; i < 16; ++i)
        {
            next_u64();
        }
    }

    // ---------------- Float API ----------------

    inline float get_rand_float()
    {
        // [0, 1)
        return (next_u64() >> 40) * (1.0f / (1ULL << 24));
    }
};

} // namespace qrtc_internal

#endif // QRTC_RNG_HPP