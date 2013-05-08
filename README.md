# Omgrofl Compiler

Compiler/interpreter for [Omgrofl](http://esolangs.org/wiki/Omgrofl).

## Preparation

Well, compile this little beast:

    make

Installation to a folder of your choice is also possible (might require "root" privileges):

    make DESTDIR=/usr install

Quite difficult, wasn't it?

## Compiling Omgrofl

Yet to be done...

## Interpreting Omgrofl

After the initial compiling of the interpreter you can either run in interactive mode using:

    ./omgrofl

Then simply type away your commands.

Or you can run an already existing source file:

    ./omgrofl sourcefile.omgrofl

No need for any special extension, shebang, or anything like that...

## Language Support

At the moment a "line ending" (\n) is completely optional. Actually multiple commands on one line will get parsed quite fine.

This will change sometimes to be conform with the official "language specification". That is, one command per line and rest ignored.

For the lulz you could write a complete "Hello, World!" in a single line. Do it while you can \o/

### Supported statements

    // assigment to values
    lool iz 72
    loool to /dev/null

    // comments
    w00t laughing at teh codez

    // incrementing/decrementing
    lmao lool
    roflmao lool

    // output
    rofl lol

    // program termination
    stfu

### Unsupported statements

    // assignment to other variables
    lool iz looool

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

    // sleeping
    afk lool
    afk 250

    // stack/queue
    haxor loool
    l33t loool
    n00b loool

These will however get implemented in the near (or far...) future.

## Examples

See [omgrofl-examples](https://github.com/mneudert/omgrofl-examples).