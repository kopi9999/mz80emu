# MainFrameApp

`MainFrameApp` is responsible for displaying and closing main application window. It also runs `mainLoop()` function (described in `main.cpp` section of documentation).

## Functions

### `OnInit()`

Returns: `bool`

| Returned value                           | Explanation                                                      |
| ---------------------------------------- | ---------------------------------------------------------------- |
| `true`                                   | main window was closed after starting the main loop              |
| `false`                                  | error while loading data occured and the main loop did not start |

`OnInit()` function opens main window and runs `mainLoop()` function.

### `OnExit()`

Returns: `int` (exit code saved in `mainLoop()` function)

`OnExit()` notifies `mainLoop()` to stop, waits until the main loop stops working and returns exit code.

### `OnFatalException()`

Returns: `void`

`OnFatalException()` handles crashes of main application window. When crash occurs, it displays a message box with information about error code and closes main window when user clicks OK button.