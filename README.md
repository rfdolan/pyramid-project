# README

**PYRAMID** - solve the maze to escape the mummy guardians!

v2.1

Copyright 2019, Mark Claypool and WPI

The code is intended to be used with the [Dragonfly game
engine](https://dragonfly.wpi.edu/), as implemented in the
book:

> Mark Claypool. Dragonfly - Program a Game Engine from Scratch,
> Interactive Media and Game Development, Worcester Polytechnic
> Institute, Version 6, 2019. Online at:
> [http://dragonfly.wpi.edu/book/](http://dragonfly.wpi.edu/book/)

## Overview

This is a class project designed for IMGD 3000 Technical Game
Development I.  The intent is to provide a framework where students
can implement a finite state machine in a game engine.  Students are
given the basic setup of a game with a Hero, a constrained space
filled with Mummy's, mystical Ankh's that should render Mummy's
momentarily paralyzed by fear and an exit to fresh air and freedom.
What is missing is AI, implemented by a state machine, that will see
the Mummy's sense, think and act as they wander, seek and attack the
Hero.

## Configure

The default configuration is to use Dragonfly v4.15. 

If using another engine or another version, there are two
configuration changes you may need to make

### STL

If you are using a version of the engine that uses `std::vector<Object
*>` instead of `ObjectList` you need to add a compile-time option to
the Makefile or project file.

+ **Windows**

    - Go to project properties: "Menu" --> "Project" --> "Properties"
  
    - Then: "C/C++" --> "Preprocessor" --> "Preprocessor Definitions" --> (Dropdown arrow) --> "Edit"

    - Add: `USE_STL` (no quotes)

+ **Linux/Mac** - Uncomment the line in the Makefile:

```
    CFLAGS:= $(CFLAGS) -DUSE_STL
```

### RegisterInterest()

If you are using a version of the engine that does *not* have
`registerInterest()` implemented, you need to remove a compile-time
option in the Makefile or project file.

+ **Windows**

    - Go to project properties: "Menu" --> "Project" --> "Properties"
  
    - Then: "C/C++" --> "Preprocessor" --> "Preprocessor Definitions" --> (Dropdown arrow) --> "Edit"

    - Remove: `DF_REGISTER_INTEREST` (no quotes)

+ **Linux/Mac** - Uncomment the line in the Makefile:

```
    CFLAGS:= $(CFLAGS) -DDF_REGISTER_INTEREST
```

Happy Pyramid plundering!

-- Mark
