//
//	A image magik import wrapper
//		to be used with dwm - on print_screen key press -> snap 
//	
//		changes in dwm config.h:
//			define key:
//				#define Print 0xff61
//			define print command:
//				static const char *printcmd[] = {"/home/develop/snap/snap", NULL};
//			add it to  static Key keys[] = {
//				{ 0, Print, spawn, {.v = printcmd} },
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// path where to put the snapshots //
#define SNAP_PATH	"~/Pictures"
// prefix of the filename //
#define SNAP_PREFIX	"snap"
#define IMGK_IMPORT "/usr/bin/import"

// auto generates a file name which not exists in SNAP_PATH
// based on date and autoincrement number
// expects a file_name buffer, file_size large
// returns strlen of file_name on success or -1 on error
int genFileName(char *file_name, int file_size) 
{
	time_t ts;
	struct tm *tm;
	int len, i = 0;
	char base_name[64];
	char *home;

	ts = time(NULL);
	tm = localtime(&ts);

	if(!(len = strftime(base_name, sizeof(base_name), SNAP_PREFIX"_%Y_%m_%d", tm))) {
		return -1;
	}

	do {
		if(SNAP_PATH[0] == '~') {
			if(SNAP_PATH[1] != '/') {
				fprintf(stderr, "invalid SNAP_PATH\n");
				return -1;
			}
			home = getenv("HOME");
			len = snprintf(file_name, file_size, "%s%s/%s_%d.png", 
					home, &(SNAP_PATH[1]), base_name, i);
		} 
		else {
			len = snprintf(file_name, file_size, "%s/%s_%d.png", SNAP_PATH, base_name, i);
		}

		i++;
	} while(access(file_name, F_OK) == 0);

	return len;
}

int main()
{
	char file_name[128];
	char *argv[5];
	int len;

	// give me an empty file name //
	if((len = genFileName(file_name, sizeof(file_name))) < 0) {
		fprintf(stderr, "Cannot generate filename\n");
		return 1;
	}
	
	// execute image magik import
	argv[0] = strdup(IMGK_IMPORT);
	argv[1] = strdup("-window");
	argv[2] = strdup("root");
	argv[3] = file_name;
	argv[4] = NULL;
	
	execvp(argv[0], argv);

	return 0;
}
