
#include "cgenerator.h"
#include "web_serv.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

extern const char *__progname;

static void
usage(void)
{
    /* TODO:3002 Don't forget to update the usage block with the most
     * TODO:3002 important options. */
    fprintf(stderr, "Usage: %s [OPTIONS]\n",
	    __progname);
    fprintf(stderr, "Version: %s\n", PACKAGE_STRING);
    fprintf(stderr, "\n");
    fprintf(stderr, " -d, --debug        be more verbose.\n");
    fprintf(stderr, " -h, --help         display help and exit\n");
    fprintf(stderr, " -v, --version      print version and exit\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "see manual page " PACKAGE "(8) for more information\n");
}

int main(int argc, char *argv[])
{
    /* this initialize variable */
    int debug = 1;
    int ch;

    /* write to usb */
    write_to_usb("AzizMemangGanteng");
    start_server();

    /* TODO:3001 If you want to add more options, add them here. */
    static struct option long_options[] = {
	{ "debug", no_argument, 0, 'd' },
	{ "help",  no_argument, 0, 'h' },
	{ "version", no_argument, 0, 'v' },
	{ 0 }
    };
    while (1) {
	int option_index = 0;
	ch = getopt_long(argc, argv, "hvdD:",
			 long_options, &option_index);
	if (ch == -1) break;
	switch (ch) {
	case 'h':
	    usage();
	    exit(0);
	    break;
	case 'v':
	    fprintf(stdout, "%s\n", PACKAGE_VERSION);
	    exit(0);
	    break;
	case 'd':
	    debug++;
	    break;
	case 'D':
	    log_accept(optarg);
	    break;
	default:
	    fprintf(stderr, "unknown option `%c'\n", ch);
	    usage();
	    exit(1);
	}
    }

    log_init(debug, __progname);

    /* TODO:3000 It's time for you program to do something. Add anything
     * TODO:3000 you want here. */
    log_info("main", "hello world!");
    log_warnx("main", "your program does nothing");

    return EXIT_SUCCESS;
}
