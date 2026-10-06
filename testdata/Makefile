PROG = smartmet-grid-test-config-creator

REQUIRES = gdal

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

CFLAGS = -DUNIX -O0 -g $(FLAGS) -Wno-unknown-pragmas

# Link against the freshly built library in the parent directory
LIBS += -L.. -lsmartmet-grid-files -lsmartmet-macgyver $(PREFIX_LDFLAGS)

all: $(PROG)

clean:
	rm -f $(PROG) *~

install:
	mkdir -p $(bindir)
	mkdir -p $(datadir)/smartmet/test/grid/engine
	rm -f $(datadir)/smartmet/test/grid/engine/*csv
	mkdir -p $(datadir)/smartmet/test/grid/library
	rm -f $(datadir)/smartmet/test/grid/library/*csv
	mkdir -p $(datadir)/smartmet/test/grid/library/test
	rm -f $(datadir)/smartmet/test/grid/library/test/*csv
	mkdir -p $(datadir)/smartmet/test/grid/redis
	$(INSTALL_DATA) grid/engine/*.cfg grid/engine/*.conf grid/engine/*.lua grid/engine/*.csv \
		$(datadir)/smartmet/test/grid/engine/
	$(INSTALL_DATA) grid/library/*csv grid/library/*dat grid/library/*png grid/library/grid-files.conf \
		$(datadir)/smartmet/test/grid/library/
	$(INSTALL_DATA) grid/library/test/*csv \
		$(datadir)/smartmet/test/grid/library/test/
	$(INSTALL_DATA) grid/redis/redis-server.rdb grid/redis/redis-template.conf \
		$(datadir)/smartmet/test/grid/redis/
	$(INSTALL_PROG) smartmet-grid-test-config-creator $(bindir)/

$(PROG) : % : %.cpp Makefile ../libsmartmet-grid-files.so
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)
