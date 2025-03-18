/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

#include "lifo_mem.h"

/**
* The read pointer and the write pointer will be the same if the lifo is empty
*/
uint8_t is_lifo_empty(lifo_mem * mem){
    return mem->rd_ptr == mem->wrt_ptr;
}

/**
* The lifo will be full when the write pointer is just behind (one position less) than the read pointer
*/
uint8_t is_lifo_full(lifo_mem * mem){
    return mem->rd_ptr == ((mem->wrt_ptr +1) % LIFO_MAX_SIZE);
}

/**
 * The data from the read pointer is read and then the read pointer is increased
 */
uint8_t lifo_pop(lifo_mem * mem, event_td * data){
    if (is_lifo_empty(mem)) return 0;

    *data = mem->buf[mem->rd_ptr];
    mem->rd_ptr = (mem->rd_ptr +1) % LIFO_MAX_SIZE;

    return 1;
}

/**
 * New data is writen in the wrt_ptr position and then this pointer is increased
 */
uint8_t lifo_push(lifo_mem * mem, event_td data){
    if(is_lifo_full(mem)) return 0;

    mem->buf[mem->wrt_ptr] = data;
    mem->wrt_ptr = (mem->wrt_ptr + 1) % LIFO_MAX_SIZE;

    return 1;
}
