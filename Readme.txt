sy is a library based on ICU that brings advanced capabilities in Max for symbol manipulation.

sy is a project by Daniele Ghisi

============

If you want to compile from source on MacOS, first download and install ICU4C. You can use the bundled version or search for the latest one.

Run:

cd icu/source
configure --enable-static --disable-shared
make
make install

ICU Headers are expected to be in /usr/local/include
ICU Static library is expected to be in /usr/local/lib