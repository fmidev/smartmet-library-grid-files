PROG = $(patsubst %.cpp,%,$(wildcard *Test.cpp))

REQUIRES = geos gdal webp filesystem

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

DEFINES = -DUNIX -D_REENTRANT -DUSE_UNSTABLE_GEOS_CPP_API
FLAGS = -std=$(CXX_STD) -Wall -W -fdiagnostics-color=$(GCC_DIAG_COLOR) -Wno-unused-parameter

ifeq ($(TSAN), yes)
  FLAGS += -fsanitize=thread
endif
ifeq ($(ASAN), yes)
  FLAGS += -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract \
           -fsanitize=undefined -fsanitize-address-use-after-scope
endif
ifeq ($(COVERAGE), yes)
  FLAGS += --coverage
endif

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

# Tests needing installed fixtures fail when they are missing. Set GRID_TEST_ALLOW_SKIP=1 to
# skip them instead, e.g. when running the tests on a host without smartmet-test-data.

all: $(PROG)

clean:
	rm -f $(PROG) *~ *.gcda *.gcno

test: $(PROG)
	@echo Running tests:
	@ok=true; \
	for prog in $(PROG); do \
	  echo "### $$prog"; \
	  ./$$prog || ok=false; \
	done; \
	$$ok

# Regenerate the synthetic GRIB fixtures and their ecCodes references (needs eccodes-devel)
synthetic:
	$(CXX) -std=$(CXX_STD) -O1 -o synthetic/make_synthetic synthetic/make_synthetic.cpp -leccodes -lfmt
	cd synthetic && ./make_synthetic .

.PHONY: synthetic

$(PROG) : % : %.cpp Makefile $(wildcard *.h) ../libsmartmet-grid-files.so
	$(CXX) $(CFLAGS) $(DEFINES) -o $@ $@.cpp $(INCLUDES) $(LIBS)
