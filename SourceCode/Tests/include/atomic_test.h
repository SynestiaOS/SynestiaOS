
#include <atomic.h>

Atomic atomic;
void should_atomic_create(void) {
  atomic_create(&atomic);
  uint32_t val = atomic_get(&atomic);
  ASSERT_EQ(val, 0);
}

Atomic atomic1;
void should_atomic_set(void) {
  atomic_create(&atomic1);
  atomic_set(&atomic1, 12);
  uint32_t val = atomic_get(&atomic1);
  ASSERT_EQ(val, 12);
}

Atomic atomic2;
uint32_t should_atomic_get(void) {
  atomic_create(&atomic2);
  atomic_set(&atomic2, 12);
  uint32_t val = atomic_get(&atomic2);
  ASSERT_EQ(val, 12);
}