#ifndef EASY80_DEBUGGER_APP_H
#define EASY80_DEBUGGER_APP_H

#include <gtk/gtk.h>

#define EASY80_DEBUGGER_APP_TYPE (easy80_debugger_app_get_type())

G_DECLARE_FINAL_TYPE(Easy80DebuggerApp, easy80_debugger_app, EASY80_DEBUGGER, APP, GtkApplication)

Easy80DebuggerApp *easy80_debugger_app_new(void);

#endif