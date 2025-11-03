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
bool exitLoop = false;

enum CrashCode exitCode = RUNNING;
bool exitedLoop = false;
bool startedLoop = false;
mutex m;

void mainLoop()
{
    exitedLoop = false;

    enum CrashCode crash;
    crash = loadConfig(&modules, &instanceInfo, &interfacesInfo, &clockInfo);
    if (crash) {exitCode = crash; exitedLoop = true; return;}
    
    crash = init(&modules, &instances, &interfaces, instanceInfo, interfacesInfo);
    if (crash) {exitCode = crash; exitedLoop = true; return;}

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockInfo.period);
    uint16_t tmpModuleId;
    Error error;
    uint32_t clockState = 0;

    startedLoop = true;

    while (!exitLoop){
        start = chrono::high_resolution_clock::now();
        end = start + duration;
        
        if (!clockStopped || nextTick) {
            for (uint32_t i = 0; i < instanceInfo.count; i++){
                if (clockInfo.strobeUpClock[i][clockState]){
                    tmpModuleId = instanceInfo.list[clockInfo.strobeUpInstanceList[i]];
                    error = modules.strobeUpFuncs[tmpModuleId](instances[clockInfo.strobeUpInstanceList[i]], interfaces[clockInfo.strobeUpInterfacesList[i]]);
                    if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
                }
            }
            
            for (uint32_t i = 0; i < instanceInfo.count; i++){
                if (clockInfo.strobeDownClock[i][clockState]){
                    tmpModuleId = instanceInfo.list[clockInfo.strobeDownInstanceList[i]];
                    error = modules.strobeDownFuncs[tmpModuleId](instances[clockInfo.strobeDownInstanceList[i]], interfaces[clockInfo.strobeDownInterfacesList[i]]);
                    if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
                }
            }
            ++clockState;
            if (clockState == clockInfo.depth) {clockState = 0;}
            
            nextTick = false;
        }
        
        do { start = chrono::high_resolution_clock::now(); } while (end > start && !clockStopped);
    }

    unloadLibs(modules.pointers, modules.count);
    
    exitCode = convertErrorToCrash(error);
    exitedLoop = true;
}

wxIMPLEMENT_APP(MainFrameApp);

thread emulator(mainLoop);

bool MainFrameApp::OnInit() {
    MainFrame *mainFrame = new MainFrame();
    mainFrame->Show();
    
    emulator.detach();

    while (!startedLoop && !exitedLoop) {}
    if (exitedLoop) {return false;}

    return true;
}

int MainFrameApp::OnExit() {
    exitLoop = true;
    while (!exitedLoop) {}
    return exitCode;
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
