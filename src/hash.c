#ifndef HASH_IMPLEMENTATION
#define HASH_IMPLEMENTATION
#include "inc/biscuit.h"

#define FNV_OFFSET_32 0x811c9dc5
#define FNV_PRIME_32 0x01000193
#define FNV_OFFSET_64 14695981039346656037ULL
#define FNV_PRIME_64 ((1ULL << 40) + (1ULL << 8) + 0xb3)

u64 fnv1a64(const void* data, size_t len) {
	u8* data_p = (u8 *)data;
	u64 hash = FNV_OFFSET_64;

	for ( u64 i = 0; i < len; i++ ) {
		hash ^= data_p[i];
		hash *= FNV_PRIME_64;
	}

	return hash;
}

u32 fnv1a32(const void* data, size_t len) {
	u8* data_p = (u8*)data;
	u32 hash = FNV_OFFSET_32;

	for ( u64 i = 0; i < len; i++ ) {
		hash ^= data_p[i];
		hash *= FNV_PRIME_32;
	}

	return hash;
}

u32 djb2(const void* data, size_t size) {
    const u8* bytes = (const u8*)data;
    
    u32 hash = 5381;
    
    for (u64 i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + bytes[i];
    }
    
    return hash;
}
#endif
