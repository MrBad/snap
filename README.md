# snap

A simple imagemagick "import" wrapper to generate different screenshots
in Linux. To be used with dwm -> add to config.h ->

#define Print                                           0xff61
static const char *printcmd[]   =       {"/home/develop/snap/snap", NULL};
..
{ 0, Print, spawn, {.v = printcmd} },

