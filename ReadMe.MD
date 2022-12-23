# CS 530 Group 6 Project
## Virtual Macroboard

|Group 6 Members|
|:---:|
|Ethan Rosenberg|
|Joshua Anthony Nicolas|
|Skylar Yoshihama|
|Jacqueline Rodriguez|
|Demarcus McKan|

### Approach
Write a C++ program that uses the Win32 library as well as Windows’ keypress hooks to both intercept user input directly from the keyboard but also send custom keyboard inputs to the OS.

|Phases   |Design/Implementation   | Time-Frame   |
|:---|:---|:---|
|Phase 1✅| **Initialization** <br> - Setup repository <br>- Deciding macro goals <br> - Create general software design | Sept-12 -> Sept 23|
|Phase 2|**Implementation** <br> - Implement code for interpreting macros| Sept 24 -> November 21|
|Phase 3|**Troubleshooting** <br> - Testing efficiency of each macro module| November 22 -> December 1|

### Deliverables
- Program Files
- Presentation

### How To Use:

# Building:
mingw32-make

# Running:
MacroBoard <path-to-macro-file | OPTIONAL>

# Writing a Macro File:
Macros are NOT case sensitive, unless you are writing a string.

Macro activation input: Either windows virtual-key codes or single letters. Space separated.

Separate input and output with a colon.

Macro outpput: Either windows virtual-key codes or letters. BUT, if you want to output text, wrap your output in quotes.
