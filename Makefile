SUBNAME = grid-files
LIB = smartmet-$(SUBNAME)
SPEC = smartmet-library-$(SUBNAME)
INCDIR = smartmet/$(SUBNAME)

REQUIRES = geos gdal webp filesystem

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

DEFINES = -DUNIX -D_REENTRANT -DUSE_UNSTABLE_GEOS_CPP_API

CFLAGS += $(shell pkg-config --cflags libopenjp2)
OPENJPEG2_LIBS += $(shell pkg-config --libs libopenjp2)

LIBS += \
	$(PREFIX_LDFLAGS) \
	$(REQUIRED_LIBS) \
	-lsmartmet-newbase \
	-lsmartmet-spine \
	-lsmartmet-macgyver \
	-lsmartmet-trax \
	-lboost_iostreams \
	-lboost_thread \
	-lpng \
	-ljpeg \
	$(OPENJPEG2_LIBS) \
	-laec \
	-lz

# What to install

LIBFILE = libsmartmet-$(SUBNAME).so

# Compilation directories

vpath %.cpp src \
			src/common \
			src/grid \
			src/grib1 \
			src/grib1/definition \
			src/grib1/implementation \
			src/grib2 \
			src/grib2/definition \
			src/grib2/implementation \
			src/identification \
			src/netcdf \
			src/querydata

vpath %.h 	src \
			src/common \
			src/grid \
			src/grib1 \
			src/grib1/definition \
			src/grib1/implementation \
			src/grib2 \
			src/grib2/definition \
			src/grib2/implementation \
			src/identification \
			src/netcdf \
			src/querydata

vpath %.o obj



# The files to be compiled

SRCS     = $(patsubst src/%,%,$(wildcard src/*.cpp src/*/*.cpp src/*/definition/*.cpp src/*/implementation/*.cpp))
OBJS     = $(SRCS:%.cpp=%.o)
OBJFILES = $(OBJS:%.o=obj/%.o)
DEPFILES = $(OBJFILES:%.o=%.d)

INCLUDES := -Isrc $(INCLUDES)


.PHONY: test rpm

# The rules

all: objdir $(LIBFILE)

#debug:
#	make create_def;
#	make obj_and_lib; 

debug: all

release: all

profile: all

#obj_and_lib: objdir $(LIBFILE)


$(LIBFILE): $(OBJFILES)
	$(CXX) $(LDFLAGS) -shared -rdynamic -o $(LIBFILE) $(OBJFILES) $(LIBS)
	@echo Checking $(LIBFILE) for unresolved references
	@if ldd -r $(LIBFILE) 2>&1 | c++filt | grep ^undefined\ symbol |\
			grep -Pv ':\ __(?:(?:a|t|ub)san_|sanitizer_)'; \
	then \
		rm -v $(LIBFILE); \
		exit 1; \
	fi

clean: 
	rm -f src/*~ src/*/*~ src/*/*/*~
	rm -rf obj
	rm -rf $(LIBFILE)
	$(MAKE) -C test $@

clean-install: 
	rm -rf $(includedir)/$(INCDIR)/*
	rm -f $(libdir)/$(LIBFILE)

format:
	clang-format -i -style=file $(SUBNAME)/*.h $(SUBNAME)/*.cpp test/*.cpp

install:
	@mkdir -p $(includedir)/$(INCDIR)
	@mkdir -p $(includedir)/$(INCDIR)/common
	@mkdir -p $(includedir)/$(INCDIR)/grid
	@mkdir -p $(includedir)/$(INCDIR)/grib1
	@mkdir -p $(includedir)/$(INCDIR)/grib1/definition
	@mkdir -p $(includedir)/$(INCDIR)/grib1/implementation
	@mkdir -p $(includedir)/$(INCDIR)/grib2
	@mkdir -p $(includedir)/$(INCDIR)/grib2/definition
	@mkdir -p $(includedir)/$(INCDIR)/grib2/implementation
	@mkdir -p $(includedir)/$(INCDIR)/identification
	@mkdir -p $(includedir)/$(INCDIR)/netcdf
	@mkdir -p $(includedir)/$(INCDIR)/querydata
	@cp src/common/*.h $(includedir)/$(INCDIR)/common
	@cp src/grid/*.h $(includedir)/$(INCDIR)/grid
	@cp src/grib1/*.h $(includedir)/$(INCDIR)/grib1
	@cp src/grib1/definition/*.h $(includedir)/$(INCDIR)/grib1/definition
	@cp src/grib1/implementation/*.h $(includedir)/$(INCDIR)/grib1/implementation
	@cp src/grib2/*.h $(includedir)/$(INCDIR)/grib2
	@cp src/grib2/definition/*.h $(includedir)/$(INCDIR)/grib2/definition
	@cp src/grib2/implementation/*.h $(includedir)/$(INCDIR)/grib2/implementation
	@cp src/identification/*.h $(includedir)/$(INCDIR)/identification	
	@cp src/netcdf/*.h $(includedir)/$(INCDIR)/netcdf	
	@cp src/querydata/*.h $(includedir)/$(INCDIR)/querydata	
	@mkdir -p $(libdir)
	$(INSTALL_PROG) $(LIBFILE) $(libdir)/$(LIBFILE)

test:
	+cd test && make test

objdir:
	@mkdir -p obj \
	          obj/common \
	          obj/grid \
	          obj/grib1 \
	          obj/grib1/definition \
	          obj/grib1/implementation \
	          obj/grib2 \
	          obj/grib2/definition \
	          obj/grib2/implementation \
	          obj/identification \
	          obj/netcdf \
	          obj/querydata

create_def:
	cd src/grib1/definition; $(MAKE) definitions;
	cd src/grib2/definition; $(MAKE) definitions;

delete_def:
	cd src/grib1/definition; $(MAKE) clean;
	cd src/grib2/definition; $(MAKE) clean;


rpm: clean $(SPEC).spec
	rm -f $(SPEC).tar.gz # Clean a possible leftover from previous attempt
	tar -czvf $(SPEC).tar.gz --transform "s,^,$(SPEC)/," *
	rpmbuild -tb $(SPEC).tar.gz
	rm -f $(SPEC).tar.gz

.SUFFIXES: $(SUFFIXES) .cpp

obj/%.o : %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c -MD -MF $(patsubst obj/%.o, obj/%.d, $@) -MT $@ -o $@ $<

obj/common/GeneralFunctions.o: CFLAGS += -Wno-deprecated-declarations

-include $(DEPFILES)
