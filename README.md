### breakpad-symbolicate

An address to symbol tool that looks at
[google-breakpad](https://code.google.com/p/google-breakpad)
symbol files.

#### Build and Install

[breakpad-symbolicate](https://github.com/breakpad-symbolicate)
depends on [google-breakpad](https://code.google.com/p/google-breakpad)
libraries. So you need to download and install
[google-breakpad](https://code.google.com/p/google-breakpad) first. You
don't need to install it.

Once you have built [google-breakpad](https://code.google.com/p/google-breakpad),
you can build breakpad-symbolicate:

    $ BREAKPAD_DIR=<path-to-google-breakpad-dir> make

