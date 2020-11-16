# Run-and-debug
An ncurses based application giving a list of all executables in a directory, and giving the user an interactive prompt with them sorted alphabetically. Once you hit enter, the program from the top will launch inside the terminal will be the application's process number and stdout. <br/> <br/>
This application was designed to be very portable and posix-compliant. Tested operating systems are GNU/Linux and FreeBSD. The makefile includes options to compile in C or C++, and with either gcc or clang.

## Build
To build the application in C with gcc, simply run:<br/>
```make```<br/> <br/>
For usage with g++, run:<br/>
```make cpp```<br/><br/>
To compile with clang in C:<br>
```make c-clang```<br/><br/>
To complie with clang in C++:<br>
```make cpp-clang```

By default the application uses ```st``` to launch terminal applications.
