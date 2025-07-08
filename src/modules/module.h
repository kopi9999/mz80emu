#ifndef MODULE
#define MODULE

#include <stdint.h>

enum Error {
    SUCCESS,
    BAD_ARGUMENT,
    MALLOC_ERROR,
};

enum Error create(void**, void*);
enum Error createInterfaces(void*, void***, uint16_t*);
enum Error strobeUp(void*, void**);
enum Error strobeDown(void*, void**);
enum Error destroy(void*);
enum Error destroyInterfaces(void*, void**, uint16_t);

#endif
