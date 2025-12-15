#ifndef MODULE
#define MODULE

#include <windows.h>
#include <stdint.h>

enum Error {
    SUCCESS,
    BAD_ARGUMENT,
    MALLOC_ERROR,
    SIZE_MISMATCH,
};

__declspec(dllexport) enum Error getName(char* out, uint32_t maxLength);
__declspec(dllexport) enum Error getDescription(char* out, uint32_t maxLength);
__declspec(dllexport) uint16_t getMajorVersion();
__declspec(dllexport) uint16_t getMinorVersion();
__declspec(dllexport) uint16_t getProtocolVersion();

_declspec(dllexport) wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces);
#endif
