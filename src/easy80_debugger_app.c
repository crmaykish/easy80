#include <gtk/gtk.h>
#include "easy80_debugger_app.h"
#include "easy80_debugger_app_win.h"

struct _Easy80DebuggerApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(Easy80DebuggerApp, easy80_debugger_app, GTK_TYPE_APPLICATION);

static void easy80_debugger_app_init(Easy80DebuggerApp *app) {

}

static void easy80_debugger_app_activate(GApplication *app) {
    Easy80DebuggerAppWindow *win;

    win = easy80_debugger_app_window_new(EASY80_DEBUGGER_APP(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void easy80_debugger_app_open(GApplication *app, GFile **files, gint n_files, const gchar *hint) {
    GList *windows;
    Easy80DebuggerAppWindow *win;
    int i;

    windows = gtk_application_get_windows(GTK_APPLICATION(app));

    if (windows) {
        win = EASY80_DEBUGGER_APP_WINDOW(windows->data);
    } else {
        win = easy80_debugger_app_window_new(EASY80_DEBUGGER_APP(app));
    }

    for (i = 0; i < n_files; i++) {
        easy80_debugger_app_window_open(win, files[i]);
    }

    gtk_window_present(GTK_WINDOW(win));
}

static void easy80_debugger_app_class_init(Easy80DebuggerAppClass *class) {
    G_APPLICATION_CLASS(class)->activate = easy80_debugger_app_activate;
    G_APPLICATION_CLASS(class)->open = easy80_debugger_app_open;
}

Easy80DebuggerApp *easy80_debugger_app_new(void) {
    return g_object_new(EASY80_DEBUGGER_APP_TYPE, "application-id", "com.cmaykish.easy80", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}