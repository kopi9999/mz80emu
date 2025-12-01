#ifndef MODULE
#define MODULE

#include <stdint.h>
#include <wx/wx.h>

enum Error {
    SUCCESS,
    BAD_ARGUMENT,
    MALLOC_ERROR,
    SIZE_MISMATCH,
};

enum Error getName(char* out, uint32_t maxLength);
enum Error getDescription(char* out, uint32_t maxLength);
uint16_t getMajorVersion();
uint16_t getMinorVersion();
uint16_t getProtocolVersion();

wxFrame* getFrame(void* instance, void** interfaces);

#endif
