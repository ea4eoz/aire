# AIRE: Apple I Replica Emulator

This is an emulator of my [RC6502 Apple 1 Replica](https://github.com/tebl/RC6502-Apple-1-Replica) single board computer for Unix-like systems. It started as a 6502 emulator but once the CPU was emulated acurately (it pass successfully [Klaus Dormann's 6502 functional tests](https://github.com/Klaus2m5/6502_65C02_functional_tests)), I added emulation of the probably the simplest 6502 computer in the world, the Apple I, but with the advantages of the RC6502 SBC: 32kb of RAM and 8kb of ROM with some built-in programs.

## Compiling

Just type 'make' or 'gmake', depending on your system.

## Usage:

Just type 'aire'. There are some command line options:
<pre>
&nbsp;&nbsp;&nbsp;&nbsp;-h,         --help          Show help.
&nbsp;&nbsp;&nbsp;&nbsp;-v,         --version       Show AIRE version.
&nbsp;&nbsp;&nbsp;&nbsp;-f,         --fastvideo     Enable fast video.
&nbsp;&nbsp;&nbsp;&nbsp;-t,         --turbo         Enable turbo mode.
&nbsp;&nbsp;&nbsp;&nbsp;-r romfile, --rom romfile   Specify ROM file.
</pre>

__Fastvideo__: The Apple I can't output to screen faster than 60 characters per second and AIRE mimmics this behaivour. The option fastvideo just disable this limitation and outputs characters as fast as possible.

__Turbo__: The Apple I runs at 1.023 MHz and AIRE tries to match that speed. Using the Turbo option makes the emulator to run as fast as possible.

__Rom__: This option is used to specify an alternate rom file. The supplied rom file comes from the [Ken Wessen's Krusader assembler](https://github.com/st3fan/krusader/tree/master) and includes Wozmon, Apple BASIC and the Krusader assembler version 1.3.

## Loading software

You can type your programs in Wozmon, just as you would do with a real Apple I, or you can paste the text into the console. Alternatively, you can use Wozmon files (text files with commands to type into the emulator) as argument when launching the emulator, for example, type:
<pre>
&nbsp;&nbsp;&nbsp;&nbsp;./aire Software/WozTest.woz
</pre>
to execute the demo/test program provided with the original Apple I user manual. Note that while loading a Wozmon file, turbo and fastvideo options are enabled.

While running, you can use these keyboard shortcuts:
<pre>
&nbsp;&nbsp;&nbsp;&nbsp;<b>Ctrl-C</b>: Quits emulator.
&nbsp;&nbsp;&nbsp;&nbsp;<b>Ctrl-R</b>: Resets CPU. RAM content is kept.
</pre>
Wozmon is the first thing you see after running the emulator. Apple BASIC is located at address 0xE000 in ROM, so to run it just type:
<pre>
&nbsp;&nbsp;&nbsp;&nbsp;<b>E000 R</b>
</pre>
Krusader assembler is located at address 0xF000 in ROM, so to run Krusader type:
<pre>
&nbsp;&nbsp;&nbsp;&nbsp;<b>F000 R</b>
</pre>
Wozmon is located at address 0xFF00, and the reset vector points to that direction, so it is loaded everytime the CPU is reset (or powered up).

Please, note you can also use Wozmon files to load and run Apple Basic and Krusader source code, see the software examples provided and explained in the next section.

## Provided Software

In the Software directory you can find some programs:

<b>Apple30thAnniversary.woz</b>: Resman's 30th Anniversary graphical demo for Apple I. Original can be found [here](https://www.applefritter.com/node/24600#comment-60100).

<b>AsciiKeycodes.woz</b>: Small utility that displays the ASCII keycodes for keyboard presses.

<b>BasicBenchmark.woz</b>: A small benchmark running in Apple Basic.

<b>Checkers.woz</b>: A Checkers game written in Apple Basic.

<b>Chess.woz</b>: Peter Jennings' Microchess written in assembler.

<b>EnhancedBasic.woz</b>: This BASIC is an adaptation to the Replica 1 from Lee E. Davidson's version for the 6502 CPU. It supports floating point.

<b>GameOfLife.woz</b>: Conway's Game of Life.

<b>Hamurabi.woz</b>: A text-based strategy game written in Apple Basic.

<b>HelloWorld.woz</b>: Hello World program using Wozmon.

<b>HelloWorldBasic.woz</b>: Hello World program using Apple Basic from Wozmon.

<b>Krusader1.woz</b>: Example on how to assemble a small program using Krusader assembler from a Woz file.

<b>Krusader2.woz</b>: A more advanced example on how to assemble a small program using Krusader assembler from a Woz file.

<b>LunarLander.woz</b> A Lunar Lander game written in assembler.

<b>LunarLanding.woz</b> Another Lunar Lander game written in Apple Basic.

<b>SlotsGame.woz</b>: A Slot Machine game written in Apple Basic.

<b>StarTrek.woz</b>: Star Trek game written by Vince Briel in Apple Basic.

<b>StarTrek_8k.woz</b>: Another Star Trek game written in Apple Basic.

<b>WozTest.woz</b>: The original test program from the Apple I user manual.

## Documentation

Some useful documentation:

<b>Apple I user manual<b>: [https://archive.org/details/applei_manual](https://archive.org/details/applei_manual)

<b>Apple BASIC user manual<b>: [https://archive.org/details/bitsavers_appleapple_1178283](https://archive.org/details/bitsavers_appleapple_1178283)

<b>Krusader 1.3 user manual<b>: [https://github.com/st3fan/krusader/blob/master/krusader13.pdf](https://github.com/st3fan/krusader/blob/master/krusader13.pdf)

<b>6502 Instruction set</b>: [https://www.masswerk.at/6502/6502_instruction_set.html](https://www.masswerk.at/6502/6502_instruction_set.html)

## License

The source files of the Apple I Replica Emulator (AIRE) in this repository are made available under the GPLv3 license. The rom file (6502.rom.bin) and example files under the Software directory are included for convenience only and all have their own license, and are not part of the Apple I Replica Emulator (AIRE).
