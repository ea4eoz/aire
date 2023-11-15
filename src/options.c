//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this program.  If not, see
//    <http://www.gnu.org/licenses/>
//

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "options.h"

aire_options options;



static void show_banner(FILE *f){
    fprintf(f, "\n");
    fprintf(f, "AIRE: Apple I Replica Emulator version 1.00\n");
    fprintf(f, "\n");
}



static void show_help(FILE *f){
    fprintf(f, "Usage:\n");
    fprintf(f, "\n");
    fprintf(f, "  aire [options] [wozfile]\n");
    fprintf(f, "\n");
    fprintf(f, "Options:\n");
    fprintf(f, "\n");
    fprintf(f, "  -h,         --help          Show this help.\n");
    fprintf(f, "  -v,         --version       Show AIRE version.\n");
    fprintf(f, "  -f,         --fastvideo     Enable fast video.\n");
    fprintf(f, "  -t,         --turbo         Enable turbo mode.\n");
    fprintf(f, "  -r romfile, --rom romfile   Specify ROM file.\n");
    fprintf(f, "\n");
    fprintf(f, "Keyboard shortcuts:\n");
    fprintf(f, "\n");
    fprintf(f, "  Ctrl-C      Quits emulator.\n");
    fprintf(f, "  Ctrl-R      Resets 6502 CPU.\n");
    fprintf(f, "\n");
}



static void set_default_options(void){
    options.flag_help = 0;
    options.flag_fastvideo = 0;
    options.flag_turbo = 0;
    options.flag_wozfile = 0;
    options.wozfile = NULL;
    options.romfile = "6502.rom.bin";
}



void parse_options(int argc, char *argv[]){
    int ch;
    opterr = 0;  // We handle getopt errors
    
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"fastvideo", no_argument, NULL, 'f'},
        {"turbo", no_argument, NULL, 't'},
        {"rom", required_argument, NULL, 'r'},
        {0, 0, 0, 0}
    };
    
    set_default_options();
    
    while ((ch = getopt_long(argc, argv, ":hvftr:", long_options, NULL)) != -1) {
        switch (ch) {
            case 'f':
                options.flag_fastvideo = 1;
                break;
                
            case 'h':
                show_help(stdout);
                exit(EXIT_SUCCESS);
                break;
                
            case 'r':
                options.romfile = optarg;
                break;

            case 't':
                options.flag_turbo = 1;
                break;
                
            case 'v':
                show_banner(stdout);
                exit(EXIT_SUCCESS);
                break;

            case ':':
                fprintf(stderr, "Error: option %c needs an argument\n\n", optopt);
                show_banner(stderr);
                show_help(stderr);
                exit(EXIT_FAILURE);
                break;
                
            case '?':
                fprintf(stderr, "Error: unknown option %c\n\n", optopt);
                show_banner(stderr);
                show_help(stderr);
                exit(EXIT_FAILURE);
                break;
        }
    }
    
    // Remaining argument
    if (optind < argc){
        options.flag_wozfile = 1;
        options.wozfile = argv[optind];
    }
}
