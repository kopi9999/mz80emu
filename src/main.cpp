#include "main.hpp"
#include "config.hpp"
#include "init.hpp"
#include "misc.hpp"
#include <chrono>
#include <iostream>
#include <thread>

#include "mainWx.hpp"
#include "MainFrame.hpp"
#include "MainFrameApp.hpp"

extern "C" {
    #include "loadMod.h"
}

using namespace std;

struct Modules modules = {};
struct UiModules uiModules = {};

void** instances;
void*** interfaces;

struct InstanceInfo instanceInfo = {};
struct UiInstanceInfo uiInstanceInfo = {};
struct InterfacesInfo interfacesInfo = {};
struct ClockInfo clockInfo = {};

bool clockStopped = true;
bool nextTick = false;
bool exitLoop = false;

enum CrashCode exitCode = RUNNING;
bool exitedLoop = false;
bool startedLoop = false;
chrono::nanoseconds duration;
chrono::nanoseconds originalDuration;

void crash() {
    wxMessageBox("Critical error occured and aplication will be closed.\nError code: " + to_string(exitCode), "Critical error.", wxOK | wxICON_ERROR);
    ::wxExit();
}

void mainLoop()
{
    exitedLoop = false;

    enum CrashCode crash;
    crash = loadConfig(&modules, &instanceInfo, &interfacesInfo, &clockInfo, &uiModules, &uiInstanceInfo);
    if (crash) {exitCode = crash; exitedLoop = true; return;}
    
    crash = init(&modules, &instances, &interfaces, instanceInfo, interfacesInfo);
    if (crash) {exitCode = crash; exitedLoop = true; return;}

    chrono::time_point<chrono::high_resolution_clock> start, end;
    duration = chrono::nanoseconds(clockInfo.period);
    originalDuration = duration;
    uint16_t tmpModuleId;
    Error error = (Error)0;
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
    wxHandleFatalExceptions(true);
    
    emulator.detach();

    return true;
}

int MainFrameApp::OnExit() {
    exitLoop = true;
    while (!exitedLoop) {}
    return exitCode;
}

void MainFrameApp::OnFatalException() {
    crash();
}

void MainFrame::OnTimer(wxTimerEvent& event) {
    if (exitCode != RUNNING) { 
        event.GetTimer().Stop();
        crash(); 
    }
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

void MainFrame::OverrideClockPeriodButton(wxCommandEvent& event) {
    if (startedLoop && !exitedLoop){
        wxTextCtrl* textControl = (wxTextCtrl*) FindWindowById(ID_CLOCK_PERIOD_TEXT_CTRL);
        if (event.IsChecked()){
            textControl->Disable();
            string value = textControl->GetLineText(0).ToStdString();
            duration = chrono::nanoseconds(stoi(value));
        }
        else {
            textControl->Enable();
            duration = originalDuration;
        }
    }
}

void MainFrame::ValidateClockPeriodValue(wxCommandEvent& WXUNUSED(event)) {
    string value = ((wxTextCtrl*) FindWindowById(ID_CLOCK_PERIOD_TEXT_CTRL))->GetLineText(0).ToStdString();
    
    bool isValid = true;
    if (value.empty() || value.length() > 10){isValid = false;}
    for (size_t i = 0; i < value.length(); i++){
        if (!isdigit(value[i])) {isValid = false; break;}
    }
    if (isValid) {
        int intValue = stol(value);
        if (intValue > 1000000000) {isValid = false;}
    }
    
    if (isValid) {((wxAnyButton*) FindWindowById(ID_OVERRIDE_CLOCK_PERIOD_BUTTON))->Enable();}
    else {((wxAnyButton*) FindWindowById(ID_OVERRIDE_CLOCK_PERIOD_BUTTON))->Disable();}
}

//test jocha
