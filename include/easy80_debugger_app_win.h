#ifndef EASY80_DEBUGGER_APP_WIN_H
#define EASY80_DEBUGGER_APP_WIN_H

#include <gtk/gtk.h>
#include "easy80_debugger_app.h"

#define EASY80_DEBUGGER_APP_WINDOW_TYPE (easy80_debugger_app_window_get_type ())

G_DECLARE_FINAL_TYPE(Easy80DebuggerAppWindow, easy80_debugger_app_window, EASY80_DEBUGGER, APP_WINDOW, GtkApplicationWindow)

Easy80DebuggerAppWindow *easy80_debugger_app_window_new(Easy80DebuggerApp *app);
void easy80_debugger_app_window_open(Easy80DebuggerAppWindow *win, GFile *file);

#endif