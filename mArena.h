#include <stdlib.h>

typedef struct {
  size_t capacity;
  size_t used;
  char *data;
} Arena;

Arena *arena_initialize(size_t capacity) {
  size_t size = sizeof(Arena) + capacity;
  Arena *arena = (Arena *)malloc(size);
  arena->used = 0;
  arena->capacity = capacity;
  arena->data = ((char *)arena) + sizeof(Arena);

  return arena;
}

char *arena_push_size(Arena *arena, size_t size) {
  if (arena->used + size >= arena->capacity) {
    size_t capacity = arena->capacity;
    capacity += size;
    capacity *= 2;

    char *newAd = (char *)realloc(arena, capacity);
    arena = (Arena *)newAd;
    arena->data = newAd + sizeof(Arena);
  }

  char *memPtr = arena->data + arena->used;
  arena->used += size;

  return memPtr;
}

void arena_free(Arena *arena) { free(arena); }

void arena_reset(Arena *arena) { arena->used = 0; }

size_t arena_size(Arena *arena) { return arena->capacity; }

size_t arena_used(Arena *arena) { return arena->used; }
