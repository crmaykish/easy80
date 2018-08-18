#include <gtk/gtk.h>
#include "easy80_debugger_app.h"

int main(int argc, char *argv[])
{
    return g_application_run(G_APPLICATION(easy80_debugger_app_new()), argc, argv);
}
