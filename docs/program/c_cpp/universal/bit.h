#include <stdint.h>
#include <assert.h>

// Generate a mask with n bits set to 1
#define LOW_N_BITS(n) (~((~(uintmax_t)0) << (n)))

#define LOWBIT(x) ((x)&(-(x)))

// Inserts specified data into a bit segment of any type
#define PACK_BITFIELD(container, value, start_bit, width) \
    ((container) = (((container) & ~((((uintmax_t)1 << (width)) - 1) << (start_bit))) | \
    ((((uintmax_t)(value)) & (((uintmax_t)1 << (width)) - 1)) << (start_bit))))
// Security version
#define S_PACK_BITFIELD(container, value, start_bit, width) \
    do { \
        assert((width) > 0 && (width) < sizeof(uintmax_t)*8); \
        assert((start_bit) + (width) <= sizeof(container)*8); \
        PACK_BITFIELD(container, value, start_bit, width); \
    } while (0)

// Extract data
#define UNPACK_BITFIELD(container, start_bit, width) \
    (((container) >> (start_bit)) & (((uintmax_t)1 << (width)) - 1))
// Security version
#define S_UNPACK_BITFIELD(container, start_bit, width) \
    (assert((width) > 0 && (width) < sizeof(uintmax_t)*8), \
     assert((start_bit) + (width) <= sizeof(container)*8), \
     (((container) >> (start_bit)) & (((uintmax_t)1 << (width)) - 1)))
