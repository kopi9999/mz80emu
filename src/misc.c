/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#include "misc.h"
#include "stddef.h"

uint16_t firstNullPointer (void** __restrict tab, uint16_t count)
{
    for (uint16_t i = 0; i < count; i++){
        if (tab[i] == NULL) {return i;}
    }
    return count;
}
