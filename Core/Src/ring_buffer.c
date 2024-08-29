#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *rb,uint8_t *mem,uint8_t *cap)
{
	rb->buffer=mem_add;
	rb->capacity=cap;

	ring_buffer_reset();


}
void ring_buffer_reset(ring) {
    head_ptr = 0;
    tail_ptr = 0;
    is_full = 0;
}

uint8_t ring_buffer_size(void) {
    uint8_t size = 0;

    if (is_full) {
        size = capacity;
    } else if (head_ptr >= tail_ptr) {
        size = head_ptr - tail_ptr;
    } else {
        size = capacity + head_ptr - tail_ptr;
    }

    return size;
}

uint8_t ring_buffer_is_full(void) {
    return is_full;
}

uint8_t ring_buffer_is_empty(void) {
    return (!is_full && (head_ptr == tail_ptr));
}

void ring_buffer_write(uint8_t data)
{
	ring_buffer[head_ptr] = data;
	head_ptr = head_ptr + 1;

	if (head_ptr >= capacity) { // si la cabeza llega al final de la memoria
	  head_ptr = 0;
	}

	if (is_full != 0) { // si se pierden datos viejos
	  tail_ptr = tail_ptr + 1;
	}

	if (tail_ptr >= capacity) { // si la cola llega al final de la memoria
	  tail_ptr = 0;
	}

	if (head_ptr == tail_ptr) { // si la cabeza alcanza la cola
	  is_full = 1;
	}
}

uint8_t ring_buffer_read(uint8_t *data) // 0x20
{
	if ((is_full != 0) || (head_ptr != tail_ptr)) { // data available
		*data = ring_buffer[tail_ptr]; // add: 0x20, val: buffer
		tail_ptr = tail_ptr + 1;
		if (tail_ptr >= capacity) {
			tail_ptr = 0;
		}
		is_full = 0;

		return 1; // buffer con datos
	}
	return 0; // buffer vacio
}
