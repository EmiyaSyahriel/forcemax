#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

LPCSTR help = 
	"Usage: forcemax.exe [args ...]\n"
	"\n"
	"Arguments:\n"
	"\t-h, --help\n"
	"\t    Show this help\n"
	"\t\n"
	"\t-c, --class-name [window_class_name=null]\n"
	"\t    Select by window class name\n"
	"\t\n"
	"\t-n, --window-name [window_name=null]\n"
	"\t    Select by window name / caption / title\n"
	"\t\n"
	"\t-h, --handle-window [hwnd=null]\n"
	"\t    Select by window handle (HWND)\n"
	"\t\n"
	"\t-r, --restore\n"
	"\t    Restore window\n"
	"\t\n"
	"\t-M, --maximize\n"
	"\t    Maximize window\n"
	"\t\n"
	"\t-b, --borderless\n"
	"\t    Make window borderless\n"
	"\t\n"
	"\t-B, --bordered\n"
	"\t    Restore window border\n"
	"\t\n"
	"\t-C, --corner\n"
	"\t    Move window to top-left of monitor (sometimes not working)\n"
	"\n"
;

LPCSTR err_nowindow =
	"Window not found"
;

int main(INT32 argc, LPCSTR argv[]) {

	BOOLEAN restore     = FALSE;
	BOOLEAN maximize    = FALSE;
	BOOLEAN borderless  = FALSE;
	BOOLEAN bordered    = FALSE;
	BOOLEAN corner      = FALSE;
	LPCSTR wndClass     = NULL;
	LPCSTR wndCapt      = NULL;
	LPCSTR handleWindow = NULL;
	HWND hWnd           = NULL;
	INT32 written       = 0;
	HANDLE stdOut       = GetStdHandle(STD_OUTPUT_HANDLE);

	// Parse Parameters
	for (INT32 i = 1; i < argc; i++) {
		LPCSTR v = argv[i];
		if (lstrcmp(v, "--help") == 0 || lstrcmp(v, "-h") == 0) {
			WriteConsole(stdOut, help, lstrlen(help), &written, NULL);
			return 0;
		}
		else if ((lstrcmp(v, "--class-name") == 0 || lstrcmp(v, "-c") == 0) && i + 1 < argc) {
			wndClass = argv[++i];
		}
		else if ((lstrcmp(v, "--window-name") == 0 || lstrcmp(v, "-n") == 0) && i + 1 < argc) {
			wndCapt = argv[++i];
		}
		else if ((lstrcmp(v, "--handle-window") == 0 || lstrcmp(v, "-h") == 0) && i + 1 < argc) {
			handleWindow = argv[++i];
		}
		else if (lstrcmp(v, "--restore") == 0 || lstrcmp(v, "-r") == 0) {
			restore = TRUE;
		}
		else if (lstrcmp(v, "--maximize") == 0 || lstrcmp(v, "-M") == 0) {
			maximize = TRUE;
		}
		else if (lstrcmp(v, "--borderless") == 0 || lstrcmp(v, "-b") == 0) {
			borderless = TRUE;
		}
		else if (lstrcmp(v, "--bordered") == 0 || lstrcmp(v, "-B") == 0) {
			bordered = TRUE;
		}
		else if (lstrcmp(v, "--corner") == 0 || lstrcmp(v, "-C") == 0) {
			corner = TRUE;
		}
	}

	if (!(wndClass != NULL || wndCapt != NULL || handleWindow != NULL) || argc <= 1) {
		WriteConsole(stdOut, help, lstrlen(help), &written, NULL);
		return 1;
	}

	if (handleWindow != NULL) {
		hWnd = (HWND)strtol(handleWindow, NULL, NULL) ;
	}

	if (hWnd == NULL) {
		hWnd = FindWindow(wndClass, wndCapt);
	}

	if (hWnd == NULL) {
		WriteConsole(stdOut, err_nowindow, lstrlen(err_nowindow), &written, NULL);
		return 1;
	}

	if (corner) {
		HMONITOR hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
		MONITORINFOEX hMI;
		ZeroMemory(&hMI, sizeof(MONITORINFOEX));

		#ifdef __TINYC__
		hMI.mi.cbSize = sizeof(MONITORINFOEX);
		#else
		hMI.cbSize = sizeof(MONITORINFOEX);
		#endif

		INT32 x, y, w, h, move;
		if (move = GetMonitorInfo(hMon, &hMI)) {

			#ifdef __TINYC__
			RECT rc = hMI.mi.rcMonitor;
			#else
			RECT rc = hMI.rcMonitor;
			#endif

			x = rc.left;
			y = rc.top;
			w = rc.right - rc.left;
			h = rc.bottom - rc.top;
		}
		if (move) SetWindowPos(hWnd, NULL, x, y, w, h, SWP_ASYNCWINDOWPOS | SWP_NOZORDER);
	}

	if (maximize || restore) {
		if (corner) {
			Sleep(500);
		}

		if (maximize) {
			PostMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		if (restore) {
			PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
	}

	if (bordered || borderless) {
		if (maximize || restore || corner) { // If setting border, wait for 500ms, for some reason window to actually maximized
			Sleep(500);
		}
		LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
		if (bordered) {
			lStyle |= (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
		}
		else if(borderless) {
			lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
		}
		SetWindowLong(hWnd, GWL_STYLE, lStyle);
	}

	return 0;
}