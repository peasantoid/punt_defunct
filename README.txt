[ Compilation ]

./make all|punt|modules|install|clean
  all: build everything
  punt: build interpreter
  modules: build modules
  install: install stuff
  clean: remove all build products

Note that you may want to run `./make clean` beforehand, as I'm not too 
good at removing build products before doing a commit. Also, stale
object files are likely to interfere with compilation.

