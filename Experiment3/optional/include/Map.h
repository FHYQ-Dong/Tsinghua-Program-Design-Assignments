/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef MAP_H
#define MAP_H

#include <string.h>

#define MAP_VERSION "0.1.0"

struct map_node_t;
typedef struct map_node_t map_node_t;


typedef struct {
  union {
   map_node_t **buckets;
   map_node_t **heads;
   map_node_t **nexts;
  };
  
  unsigned nbuckets, nnodes, nkeysize;
} map_base_t;


typedef struct map_iter_t {
  unsigned bucketidx;
  map_node_t *node;
  void* opaque;
} map_iter_t;


#define map_t(T)\
  struct { map_base_t base; T *ref; T tmp; }


#define map_init(m)\
  memset(m, 0, sizeof(*(m)))


#define map_deinit(m)\
  map_deinit_(&(m)->base)


#define map_get(m, key)\
  ( (m)->ref = map_get_(&(m)->base, key) )


#define map_set(m, key, value)\
  ( (m)->tmp = (value),\
    map_set_(&(m)->base, key, &(m)->tmp, sizeof((m)->tmp)) )


#define map_remove(m, key)\
  map_remove_(&(m)->base, key)


#define map_resize(m, n)\
  map_resize_(&(m)->base, n)


#define map_iter(m)\
  map_iter_()


#define map_iter_remove(m, iter)\
  map_iter_remove_(&(m)->base, iter)


#define map_next(m, iter)\
  map_next_(&(m)->base, iter)


////// can use primitive types as key //////
#define map_ex_t(KT, VT)\
  struct { map_base_t base; VT *ref; VT tmp; union { KT k; const void* kbox; }; }


#define map_init_ex(m)\
  map_init(m);\
  (m)->base.nkeysize = sizeof((m)->k);


#define map_deinit_ex(m)\
  map_deinit(m)


#define map_get_ex(m, key)\
  ( (m)->kbox = (const void*)key,\
    (m)->ref = map_get_(&(m)->base, (m)->kbox))


#define map_set_ex(m, key, value)\
  ( (m)->kbox = (const void*)key,\
    (m)->tmp = (value),\
    map_set_(&(m)->base, (m)->kbox, &(m)->tmp, sizeof((m)->tmp)) )


#define map_remove_ex(m, key)\
  ( (m)->kbox = (const void*)key,\
    map_remove_(&(m)->base, (m)->kbox))


#define map_resize_ex(m, n)\
  map_resize(m, n)


#define map_iter_ex(m)\
  map_iter(m)


#define map_iter_remove_ex(m, iter)\
  map_iter_remove(m, iter)


#define map_next_ex(m, iter)\
  map_next(m, iter)


////// public methods //////
void map_deinit_(map_base_t *m);
void *map_get_(map_base_t *m, const void *key);
int map_set_(map_base_t *m, const void *key, void *value, unsigned vsize);
void map_remove_(map_base_t *m, const void *key);
map_iter_t map_iter_(void);
map_iter_t* map_iter_remove_(map_base_t *m, map_iter_t *iter);
typedef int (*Iter_Visitor_Func)(const void* key, const void* value);
int map_iter_acceptor_(map_iter_t *iter, Iter_Visitor_Func cb);
const void *map_next_(map_base_t *m, map_iter_t *iter);
/*for earlier reserving space usage*/
int map_resize_(map_base_t *m, unsigned nbuckets);


typedef map_t(void*) map_void_t;
typedef map_t(char*) map_str_t;
typedef map_t(int) map_int_t;
typedef map_t(char) map_char_t;
typedef map_t(float) map_float_t;
typedef map_t(double) map_double_t;


typedef map_ex_t(int, int) map_int2int_t;
typedef map_ex_t(int, void*) map_int2pvoid_t;


#endif