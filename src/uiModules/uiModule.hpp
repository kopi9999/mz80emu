/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

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

wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces);

#endif
