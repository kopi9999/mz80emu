# MainFrame

`MainFrame` is a definition of main emulator control panel and is responsible for handling the window events. It contains the window layout, and controls responsible for flow control.

## Buttons

| Button | Connected function | Description |
| - | - | - |
| `File / Quit` | `OnQuit()` | Quits emulator |
| `Stop clock` (pause icon) | `stopClock()` | Freezes emulator in one state |
| `Run clock` (run icon) | `runClock()` | Resumes emulator from stopped state |
| `Next tick` (arrow icon) | `nextTick()` | Triggers one clock cycle in stopped state |
| `Override clock` (toggle) | `OverrideClockPeriodButton()` | Overwrites value of clock period when toggled |

## Inputs

| Input                                      | Connected Function           | Description                                                  |
| ------------------------------------------ | ---------------------------- | ------------------------------------------------------------ |
| `ID_CLOCK_PERIOD_TEXT_CTRL` (text control) | `ValidateClockPeriodValue()` | Holds value for clock period override. When the value given is invalid, the function disables `Override clock` toggle. |

## Event handler functions

| function                      | description                                                  |
| ----------------------------- | ------------------------------------------------------------ |
| `RunClock()`                  | changes `clockStopped`  global variable to true              |
| `StopClock()`                 | changes `clockStopped`  global variable to false             |
| `NextTick()`                  | changes `nextTick` to true                                   |
| `OverrideClockPeriodButton()` | changes `duration` global variable to one set by user in text control, or restores it to it's original value |
| `ValidateClockPeriodValue()`  | Validates if text control value is a number between 0 and 1000000000. If it is not, the `Overwrite clock` toggle becomes disabled. |
| `OnTimer()`                   | When `exitCode`is not running,                               |