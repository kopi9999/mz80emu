/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 Daw151
 * This file is a part of mz80emu project.
 */

#ifndef MAIN_FRAME_APP
#define MAIN_FRAME_APP
#define WinMain main
#include <wx/wx.h>

class MainFrameApp : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnExit();
    virtual void OnFatalException();
};

#endif
