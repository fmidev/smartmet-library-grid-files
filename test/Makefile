PROG = $(patsubst %.cpp,%,$(wildcard *Test.cpp))

REQUIRES = geos gdal webp filesystem

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

DEFINES = -DUNIX -D_REENTRANT -DUSE_UNSTABLE_GEOS_CPP_API
FLAGS = -std=$(CXX_STD) -Wall -W -fdiagnostics-color=$(GCC_DIAG_COLOR) -Wno-unused-parameter

CFLAGS = -DUNIX -O0 -g $(FLAGS)

INCLUDES += -I../src

# Link against the freshly built library in the parent directory and its dependencies,
# mirroring the library's own Makefile.
LIBS += ../libsmartmet-grid-files.so \
	$(REQUIRED_LIBS) \
	-lsmartmet-newbase \
	-lsmartmet-spine \
	-lsmartmet-macgyver \
	-lsmartmet-trax \
	$(PREFIX_LDFLAGS)

all: $(PROG)

clean:
	rm -f $(PROG) *~

test: $(PROG)
	@echo Running tests:
	@ok=true; \
	for prog in $(PROG); do \
	  ./$$prog || ok=false; \
	done; \
	$$ok

$(PROG) : % : %.cpp Makefile ../libsmartmet-grid-files.so
	$(CXX) $(CFLAGS) $(DEFINES) -o $@ $@.cpp $(INCLUDES) $(LIBS)
