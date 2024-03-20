# forcemax
Force Windows window to maximize and additionally make it borderless, useful for games that has it's maximize button is disabled e.g DMM version of デレステ

[Download Latest](https://github.com/EmiyaSyahriel/forcemax/releases/latest) | [All Downloads](https://github.com/EmiyaSyahriel/forcemax/releases)

## System Requirements
- Windows 10 64-bit (for release, Vista 32-bit if recompiled using C compiler of that age)
- 50kB of free storage
- 100kB of free RAM

## Features
- Maximize window
- Remove / restore window border
- Return the window border (not guaranteed to be the same border, just works for the most)

## Usage
- `-h, --help`<br/>
    Show help

- `-c, --class-name [window_class_name=null]`<br/>
    Select by window class name

- `-n, --window-name` [window_name=null]<br/>
    Select by window name / caption / title

- `-h, --handle-window` [hwnd=null]<br/>
    Select by window handle (HWND)

- `-r, --restore`<br/>
    Restore window

- `-M, --maximize`<br/>
    Maximize window

- `-b, --borderless`<br/>
    Make window borderless

- `-B, --bordered`<br/>
    Restore window border

- `-C, --corner`<br/>
    Move window to top-left of monitor (sometimes not working)

> If the target window is elevated / launched using Run As Administrator (e.g デレステ DMM ver.), this program
> will also needs to be run on elevated environment (e.g `cmd` that is launched using Run as Administrator)
> or otherwise no effect will be working.

## Building
see [Building](BUILDING.MD)

## License
Creative Commons Attribution 4.0, see [LICENSE](LICENSE.MD)