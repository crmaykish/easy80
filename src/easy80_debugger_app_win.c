#include <gtk/gtk.h>
#include "easy80_debugger_app.h"
#include "easy80_debugger_app_win.h"

struct _Easy80DebuggerAppWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(Easy80DebuggerAppWindow, easy80_debugger_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void easy80_debugger_app_window_init(Easy80DebuggerAppWindow *app) {

}

static void easy80_debugger_app_window_class_init(Easy80DebuggerAppWindowClass *class) {

}

Easy80DebuggerAppWindow *easy80_debugger_app_window_new(Easy80DebuggerApp *app) {
    return g_object_new(EASY80_DEBUGGER_APP_WINDOW_TYPE, "application", app, NULL);
}

void easy80_debugger_app_window_open(Easy80DebuggerAppWindow *win, GFile *file) {

}