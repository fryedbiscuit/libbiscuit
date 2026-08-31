// Biscuit's expandable arenas
// if flagged as expandable they expand when out of space
// essentially arena linked lists
// allocation and freeing are recursive functions

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define ALIGN_16(size) (((size) + 15) & ~15)

typedef struct Arena {
	uint8_t* buffer;
	size_t size;
	size_t offset;
	bool expandable;
	struct Arena* next;
	void* (*allocator)(size_t size);
	void (*free)(void* buffer);
} Arena;

// Initializes an arena struct and allocates memory with malloc
void arena_init(Arena* arena, size_t size, bool expandable);

void* arena_alloc(Arena* arena, size_t size);
void* arena_calloc(Arena* arena, size_t size);
void arena_clear(Arena*);

void arena_free(Arena* arena);

static inline void arena_expand(Arena* arena);

// ------------------------ arena.c ---------------------------- //
#ifndef ARENA_IMPLEMENTATION
#define ARENA_IMPLEMENTATION

void arena_init(Arena* arena, size_t size, bool expandable) {
	uint8_t* buffer = (uint8_t*)malloc(size);

	*arena = (Arena){
		.buffer = buffer,
		.size = ALIGN_16(size),
		.offset = 0,
		.expandable = expandable,
		.next = NULL,
		.allocator = malloc,
		.free = free,
	};
}

void* arena_alloc(Arena* arena, size_t size) {
	if (size > arena->size) {
		return NULL;
	} else if (size <= (arena->size - arena->offset)) {
		size_t aligned_size = ALIGN_16(size);
		void* ptr = &arena->buffer[arena->offset];
		arena->offset += aligned_size;
		return ptr;
	} else {
		if (arena->expandable) {
			if (arena->next == NULL) {
				arena_expand(arena);
				return arena_alloc(arena->next,size);
			} else {
				return arena_alloc(arena->next,size);
			}
		} else {
			return NULL;
		}
	}
};

void* arena_calloc(Arena* arena, size_t size) {
	void* ptr = arena_alloc(arena, size);
	memset(ptr,0,ALIGN_16(size));
	return ptr;
}

void arena_clear(Arena* arena){
	arena->offset = 0;
}

void arena_free(Arena* arena) {
	if (arena->next != NULL) {
		arena_free(arena->next);
		arena->free(arena->next);
	}
	arena->free(arena->buffer);
	arena->buffer = NULL;
}

static inline void arena_expand(Arena* arena){
	Arena* new_arena = (Arena*)arena->allocator(sizeof(Arena));

	*new_arena = (Arena){
		.buffer = (uint8_t*)malloc(arena->size),
		.size = arena->size,
		.offset = 0,
		.expandable = arena->expandable,
		.next = NULL,
		.allocator = arena->allocator,
		.free = arena->free,
	};

	arena->next = new_arena;
}
#endif
