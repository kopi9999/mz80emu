#ifndef MODULE
#define MODULE

#include <windows.h>
#include <stdint.h>

enum Error {
    SUCCESS,
    BAD_ARGUMENT,
    MALLOC_ERROR,
};

__declspec(dllexport) enum Error getName(char* out, uint32_t maxLength);
__declspec(dllexport) enum Error getDescription(char* out, uint32_t maxLength);
__declspec(dllexport) uint16_t getMajorVersion();
__declspec(dllexport) uint16_t getMinorVersion();
__declspec(dllexport) uint16_t getProtocolVersion();

__declspec(dllexport) enum Error create(void**, void*);
__declspec(dllexport) enum Error createInterfaces(void*, void***, uint16_t*);
__declspec(dllexport) enum Error strobeUp(void*, void**);
__declspec(dllexport) enum Error strobeDown(void*, void**);
__declspec(dllexport) enum Error destroy(void*);
__declspec(dllexport) enum Error destroyInterfaces(void*, void**, uint16_t);

#endif
