# Run-and-debug
An ncurses based application giving a list of all executables in a directory, and giving the user an interactive prompt with them sorted alphabetically. Once you hit enter, the program from the top will launch inside the terminal will be the application's process number and stdout.

## Build
Execute the command in the same directory as the program.<br/>
```cc -lncurses -o list_files list_files.c```
Or use the c++ compiler
```c++ -lncurses -o list_files list_files.cpp```
<br/>By default the application uses ```st``` to launch terminal applications.<br/>
