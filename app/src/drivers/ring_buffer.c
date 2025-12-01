#include "ring_buffer.h"

static uint16_t advance_index(const ring_buffer_t *rb, uint16_t idx){
  idx++;
  if(idx >= rb->size){
    idx=0;
  }
  return idx;
}

void rb_init(ring_buffer_t *rb, volatile uint8_t *storage, uint16_t size){
  rb->head = 0;
  rb->tail = 0;
  rb->size = size;
  rb->buf = storage;
}

int rb_push_isr(ring_buffer_t *rb, uint8_t data){
  uint16_t next_head = advance_index(rb, rb->head);

  if(next_head == rb->tail){
    return -1;
  }

  rb->buf[rb->head] = data;
  rb->head = next_head;
  return 0;
}

int rb_pop(ring_buffer_t *rb, uint8_t *out){

  if(rb->head == rb->tail){
    return -1;
  }

  *out = rb->buf[rb->tail];
  rb->tail = advance_index(rb, rb->tail);
  return 0;
}
