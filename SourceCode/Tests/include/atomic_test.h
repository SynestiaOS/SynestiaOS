
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

Atomic atomic3;
uint32_t should_atomic_inc(){
  atomic_create(&atomic3);
  atomic_set(&atomic3, 12);
  uint32_t val = atomic_get(&atomic3);
  ASSERT_EQ(val, 12);
  atomic_inc(&atomic3);
  val = atomic_get(&atomic3);
  ASSERT_EQ(val, 13);
  atomic_inc(&atomic3);
  val = atomic_get(&atomic3);
  ASSERT_EQ(val, 14);
}

Atomic atomic4;
uint32_t should_atomic_dec(){
  atomic_create(&atomic4);
  atomic_set(&atomic4, 12);
  uint32_t val = atomic_get(&atomic4);
  ASSERT_EQ(val, 12);
  atomic_dec(&atomic4);
  val = atomic_get(&atomic4);
  ASSERT_EQ(val, 11);
  atomic_dec(&atomic4);
  val = atomic_get(&atomic4);
  ASSERT_EQ(val, 10);
}

Atomic atomic5;
uint32_t should_atomic_add(){
  atomic_create(&atomic5);
  atomic_set(&atomic5, 12);
  uint32_t val = atomic_get(&atomic5);
  ASSERT_EQ(val, 12);
  atomic_add(&atomic5,2);
  val = atomic_get(&atomic5);
  ASSERT_EQ(val, 14);
  atomic_add(&atomic5,3);
  val = atomic_get(&atomic5);
  ASSERT_EQ(val, 17);
}

Atomic atomic6;
uint32_t should_atomic_sub(){
  atomic_create(&atomic6);
  atomic_set(&atomic6, 12);
  uint32_t val = atomic_get(&atomic6);
  ASSERT_EQ(val, 12);
  atomic_sub(&atomic6,2);
  val = atomic_get(&atomic6);
  ASSERT_EQ(val, 10);
  atomic_sub(&atomic6,3);
  val = atomic_get(&atomic6);
  ASSERT_EQ(val, 7);
}