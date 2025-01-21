
include $(shell smartbuildcfg --prefix)/share/smartmet/devel/makefile.inc

PROG = $(patsubst %.cpp,%,$(wildcard *Test.cpp))

COMPILE_TESTS=$(wildcard *Compile.cpp)

CFLAGS = -DUNIX -D_REENTRANT -O0 -g $(FLAGS)

LIB_TO_TEST := -L ../ -lsmartmet-grid-files

LIBS += $(PREFIX_LDFLAGS) \
	$(LIB_TO_TEST) \
	$(REQUIRED_LIBS) \
	-lboost_thread \
	-lboost_system \
	-lpthread

INCLUDES += -I ../src/common -I /usr/include/smartmet

all: $(PROG)

clean:
	rm -f $(PROG) *~ *.err
	rm -rf obj

test: $(PROG)
	@ok=true; \
	for prog in $(PROG); do \
		echo "Running program: $$prog"; \
		./$$prog || ok=false; \
	done; \
	$$ok

$(PROG) : % : obj/%.o ../libsmartmet-grid-files.so
	$(CXX) -Wl,--rpath,$(shell pwd)/.. $(CFLAGS) $< $(LIBS) -o $@

obj/%.o: %.cpp
	@mkdir -p obj
	$(CXX) $(CFLAGS) $(INCLUDES) -c -MD -MF $(patsubst obj/%.o, obj/%.d, $@) -MT $@ -o $@ $<

ifneq ($(wildcard obj/*.d),)
-include $(wildcard obj/*.d)
endif
