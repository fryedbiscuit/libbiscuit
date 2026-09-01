// Biscuit's expandable arenas
// if flagged as expandable they expand when out of space
// essentially arena linked lists
// allocation and freeing are recursive functions

#include "inc/biscuit.h"
#include "inc/sys.h"

#define ALIGN_16(size) (((size) + 15) & ~15)

// Initializes an arena struct and allocates memory
void arena_init(Arena* arena, u64 size, bool expandable);

void* arena_alloc(Arena* arena, u64 size);
void* arena_calloc(Arena* arena, u64 size);
void arena_clear(Arena*);

void arena_free(Arena* arena);

void arena_expand(Arena* arena);

// ------------------------ arena.c ---------------------------- //
#ifndef ARENA_IMPLEMENTATION
#define ARENA_IMPLEMENTATION

void arena_init(Arena* arena, u64 size, bool expandable) {
	u8* buffer = (u8*)alloc(size);

	*arena = (Arena){
		.buffer = buffer,
		.size = ALIGN_16(size),
		.offset = 0,
		.expandable = expandable,
		.next = NULL,
		.allocator = alloc,
		.free = alloc_free,
	};
}

void* arena_alloc(Arena* arena, u64 size) {
	if (size > arena->size) {
		return NULL;
	} else if (size <= (arena->size - arena->offset)) {
		u64 aligned_size = ALIGN_16(size);
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
}

void* arena_calloc(Arena* arena, u64 size) {
	void* ptr = arena_alloc(arena, size);
	bc_memset(ptr,0,ALIGN_16(size));
	return ptr;
}

void arena_clear(Arena* arena){
	arena->offset = 0;
	if (arena->next) {
		//free the buffers, retroactivelly
		arena_free(arena->next);

		//free the arena struct
		arena->free(arena->next);

		arena->next = NULL;
	}
}

void arena_free(Arena* arena) {
	if (arena->next != NULL) {
		arena_free(arena->next);
		arena->free(arena->next);
	}
	arena->free(arena->buffer);
	arena->buffer = NULL;
}

void arena_expand(Arena* arena){
	Arena* new_arena = (Arena*)arena->allocator(sizeof(Arena));

	*new_arena = (Arena){
		.buffer = (u8*)arena->allocator(arena->size),
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
