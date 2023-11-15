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

#ifndef options_h
    #define options_h
    #include <stdint.h>

    typedef struct{
        uint16_t flag_help;
        uint8_t flag_fastvideo;
        uint8_t flag_turbo;
        uint8_t flag_wozfile;
        char *wozfile;
        char *romfile;
    } aire_options;

    extern aire_options options;

    void parse_options(int argc, char *argv[]);
#endif
