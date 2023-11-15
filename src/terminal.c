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

#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "options.h"
#include "terminal.h"
#include "timeutils.h"

// Timespec struct with 20 milliseconds
static const struct timespec stdin_polling_interval = {
    .tv_sec = 0,
    .tv_nsec = 20000000
};

static struct timespec last_char_timestamp, last_key_timestamp;
static struct termios oldt;
static int oldf, stdin_value;
static uint8_t last_key, stdin_has_data = 0;
static FILE *wozfile;
static long wozsize;

int ACTION = 0;



// Restore computer terminal to previous state
static void restore_terminal(void){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
}



// Executed whenever the program exists AND terminal
// has been configured into RAW mode
static void exit_hook(void){
    printf("\n*** Ctrl-C ***\n");
    restore_terminal();    
}



// Polling the keyboard (stdin) as frequently as
// the 6502 CPU does in the Apple 1 produces an excesive
// CPU usage. Here we are limiting the polling interval
// (to stdin) to 20 ms
static void *stdin_handler(void *args){
    while(1){
        nanosleep(&stdin_polling_interval, NULL);
        int ch = getchar();
        if (ch != EOF){
            switch(ch){
                case CTRL_C:
                    exit(EXIT_SUCCESS);
                    break;
                case CTRL_R:
                    ACTION = ACTION_RESET;
                    break;
                default:
                    stdin_value = ch;
                    stdin_has_data = 1;
                    break;
            }
        }
    }
    return NULL;
}



void configure_terminal(void){
    // If there is a wozfile, open it, get its size, and rewind it.
    if(options.flag_wozfile){
        wozfile = fopen(options.wozfile, "rb");
        if (wozfile==NULL){
            fprintf(stderr, "Error: can't open %s\n", options.wozfile);
            exit(EXIT_FAILURE);
        }
        fseek(wozfile, 0L, SEEK_END);
        wozsize = ftell(wozfile);
        rewind(wozfile);
    }

    // Configure the terminal for raw mode
    tcgetattr(STDIN_FILENO, &oldt);
    struct termios newt = oldt;
    newt.c_iflag &= ~(ICRNL | IXON);
    newt.c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
    
    // Setup exit hook
    atexit(exit_hook);
    
    // Also initializes these variables
    clock_gettime(CLOCK_MONOTONIC, &last_char_timestamp);
    last_key_timestamp = last_char_timestamp;
    
    // and start the stdin processing thread
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &stdin_handler, NULL);
}



// Checks if a key has been typed
uint8_t check_keyboard_ready(void){
    int ch = 0;
    if (options.flag_wozfile){
        if (wozsize){
            ch = fgetc(wozfile);
            wozsize--;
            if (wozsize == 0L){
                // That was the last character
                // in file. Deactivate woz mode
                fclose(wozfile);
                options.flag_wozfile = 0;
            }
        }
    } else {
        if (stdin_has_data){
            ch = stdin_value;
            stdin_has_data = 0;
        } else {
            ch = EOF;
        }
    }

    if (ch != EOF){
        if (ch == 0x0A){ // LF?
            ch = 0x0D;   // Apple 1 uses CR
        }
        ch = toupper(ch);
        last_key = ((uint8_t)ch)|0x80; // Bit 7 set to one
    }

    return (ch != EOF);
}



uint8_t read_keyboard(void){
    return last_key;
}



// Check for terminal ready
uint8_t check_terminal_busy(void){
    if (options.flag_fastvideo | options.flag_wozfile){
        return 0;
    } else {
        struct timespec now, elapsed;
        clock_gettime(CLOCK_MONOTONIC, &now);
        timerspecsub(&now, &last_char_timestamp, &elapsed);
        long us = timespec_to_us(&elapsed);
        // The Apple 1 video circuit can't output characters faster than
        // 60 chars per second. This would be 1 / 60 = 16666 us delay
        return (us < 16666);
    }
}



// Write to the terminal
void write_terminal(uint8_t byte){
    static int char_counter = 0;
    // Only 7 bits configured for output
    byte &= 0x7F;
    byte = (uint8_t)toupper((int)byte);
    clock_gettime(CLOCK_MONOTONIC, &last_char_timestamp);
    if ((byte == 0x0D) | (byte >= 32)){
        if (byte == 0x0D){
            putchar('\n');
            char_counter = 0;
        } else {
            putchar(byte);
            char_counter++;
        }
        // Apple 1 screen is only
        // 40 characters wide
        if (char_counter == 40){
            putchar('\n');
            char_counter = 0;
        }
        fflush(stdout);
    }
}
