#include "main.hpp"
#include "config.hpp"
#include "init.hpp"
#include "misc.hpp"
#include <chrono>
#include <iostream>
#include <thread>

#include "MainFrame.hpp"
#include "MainFrameApp.hpp"
#include <wx/wx.h>
#include <wx/evtloop.h>

extern "C" {
    #include "loadMod.h"
}

using namespace std;

struct Modules modules = {};

void** instances;
void*** interfaces;

struct InstanceInfo instanceInfo = {};
struct InterfacesInfo interfacesInfo = {};
struct ClockInfo clockInfo = {};

bool clockStopped = false;
bool nextTick = false;

void mainLoop(wxWeakRef<MainFrame> mainFrame)
{
    enum CrashCode crash;
    crash = loadConfig(&modules, &instanceInfo, &interfacesInfo, &clockInfo);
    if (crash) {return;}
    //if (crash) {return crash;}
    
    crash = init(&modules, &instances, &interfaces, instanceInfo, interfacesInfo);
    if (crash) {return;}
    //if (crash) {return crash;}

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockInfo.period);
    uint16_t tmpModuleId;
    Error error;
    uint32_t clockState = 0;

    wxEventLoopBase* mainLoop = wxEventLoop::GetActive()
                                ? wxEventLoop::GetActive() 
                                : new wxEventLoop();
    wxEventLoopBase::SetActive(mainLoop);

    while (mainLoop && mainFrame && mainFrame->IsShownOnScreen()){
        start = chrono::high_resolution_clock::now();
        end = start + duration;
        
        if (!clockStopped || nextTick) {
            for (uint32_t i = 0; i < instanceInfo.count; i++){
                if (clockInfo.strobeUpClock[i][clockState]){
                    tmpModuleId = instanceInfo.list[clockInfo.strobeUpInstanceList[i]];
                    error = modules.strobeUpFuncs[tmpModuleId](instances[clockInfo.strobeUpInstanceList[i]], (void**) &interfaces[clockInfo.strobeUpInterfacesList[i]]);
                    if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
                }
            }
            
            for (uint32_t i = 0; i < instanceInfo.count; i++){
                if (clockInfo.strobeDownClock[i][clockState]){
                    tmpModuleId = instanceInfo.list[clockInfo.strobeDownInstanceList[i]];
                    error = modules.strobeDownFuncs[tmpModuleId](instances[clockInfo.strobeDownInstanceList[i]], (void**) &interfaces[clockInfo.strobeDownInterfacesList[i]]);
                    if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
                }
            }
            ++clockState;
            if (clockState == clockInfo.depth) {clockState = 0;}
            
            nextTick = false;
        }
        
        do {
            if (mainLoop && mainLoop->Pending() && mainFrame && mainFrame->IsShownOnScreen()) { mainLoop->Dispatch(); }
            if (mainLoop && mainFrame && mainFrame->IsShownOnScreen()) { mainLoop->ProcessIdle(); }
            start = chrono::high_resolution_clock::now();
        } while (end > start && !clockStopped);
    }

    wxEventLoopBase::SetActive(nullptr);
    delete mainLoop;
    unloadLibs(modules.pointers, modules.count);
    //return convertErrorToCrash(error);
}

wxIMPLEMENT_APP(MainFrameApp);

bool MainFrameApp::OnInit() {
    MainFrame *mainFrame = new MainFrame();
    mainFrame->Show();

    mainLoop(mainFrame);

    return false;
}

void MainFrame::StopClock(wxCommandEvent& WXUNUSED(event)) {
    clockStopped = true;
}

void MainFrame::RunClock(wxCommandEvent& WXUNUSED(event)) {
    clockStopped = false;
}

void MainFrame::NextTick(wxCommandEvent& WXUNUSED(event)) {
    nextTick = true;
}

//test jocha
