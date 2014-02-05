# Omgrofl Compiler

Compiler/interpreter for [Omgrofl](http://esolangs.org/wiki/Omgrofl).


## Preparation

Well, compile this little beast:

    make

Installation to a folder of your choice is also possible
(might require "root" privileges):

    make DESTDIR=/usr install

Quite difficult, wasn't it?


## Compiling Omgrofl

Yet to be done...

## Interpreting Omgrofl

After the initial compiling of the interpreter you can either
run in interactive mode using:

    ./omgrofl

Then simply type away your commands.

Or you can run an already existing source file:

    ./omgrofl sourcefile.omgrofl

No need for special extensions, a shebang, or anything like that...

Shebangs are supported by the way! Any line matching the pattern
*#!/.+/omgrofl* is ignored from parsing (no spaces allowed there!).
So as long as you have installed it under the name "omgrofl" you
are ready to go!


## Language Support

### Supported statements

Everything is case-insensitive!

Multiple statements per line are allowed.
Only a comment has to be followed by a linebreak.

    // assignment
    lool iz 72
    loool to /dev/null
    lol iz lool

    // comments
    w00t laughing at teh codez

    // incrementing/decrementing
    lmao lool
    roflmao lool

    // output
    rofl lol

    // sleeping
    afk lool
    afk 250

    // program termination
    stfu

    // multi-statement lines
    lol iz 79 rofl lol lol iz 75 rofl lol

### Unsupported statements

    // conditions
    wtf lool iz liek loool
      ...
    brb

    wtf lol iz nope uber 100
      ...
    brb

    // input
    stfw lol

    // looping
    rtfm
      ...
      tldr
    brb

    4 lol iz 0 2 10
      ...
    end

    // stack/queue
    haxor loool
    l33t loool
    n00b loool

These will however get implemented in the near (or far...) future.


## Examples

See [omgrofl-examples](https://github.com/mneudert/omgrofl-examples).
