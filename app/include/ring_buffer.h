
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

typedef struct {
  volatile uint16_t head;
  volatile uint16_t tail;
  uint16_t size;
  volatile uint8_t *buf;

} ring_buffer_t;

static uint16_t advance_index(const ring_buffer_t *rb, uint16_t idx);
void rb_init(ring_buffer_t *rb, volatile uint8_t *storage, uint16_t size);
int rb_push_isr(ring_buffer_t *rb, uint8_t data);
int rb_pop(ring_buffer_t *rb, uint8_t *out);

#endif
