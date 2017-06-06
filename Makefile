SUBNAME = grid-files
LIB = smartmet-$(SUBNAME)
SPEC = smartmet-library-$(SUBNAME)
INCDIR = smartmet/$(SUBNAME)

# Installation directories

processor := $(shell uname -p)

ifeq ($(origin PREFIX), undefined)
  PREFIX = /usr
else
  PREFIX = $(PREFIX)
endif

ifeq ($(processor), x86_64)
  libdir = $(PREFIX)/lib64
else
  libdir = $(PREFIX)/lib
endif

bindir = $(PREFIX)/bin
includedir = $(PREFIX)/include
datadir = $(PREFIX)/share
objdir = obj

# Compiler options

DEFINES = -DUNIX -D_REENTRANT

ifeq ($(CXX), clang++)

 FLAGS = \
	-std=c++11 -fPIC -MD \
	-Weverything \
	-Wno-c++98-compat \
	-Wno-float-equal \
	-Wno-padded \
	-Wno-missing-prototypes

 INCLUDES = \
	-isystem $(includedir) \
	-isystem $(includedir)/smartmet

else

 FLAGS = -std=c++11 -fdiagnostics-color=always -fPIC -MD -Wall -W -Wno-unused-parameter

 FLAGS_DEBUG = \
	-Wcast-align \
	-Winline \
	-Wno-multichar \
	-Wno-pmf-conversions \
	-Woverloaded-virtual  \
	-Wpointer-arith \
	-Wcast-qual \
	-Wredundant-decls \
	-Wwrite-strings \
	-Wno-sign-promo \
	-Wno-unknown-pragmas \
	-Wno-inline

 FLAGS_RELEASE = -Wuninitialized

 INCLUDES = \
	-I$(includedir) \
	-I$(includedir)/smartmet \
	$(pkg-config --cflags icu-i18n) \

endif

# Compile options in detault, debug and profile modes

CFLAGS         = $(DEFINES) $(FLAGS) $(FLAGS_RELEASE) -DNDEBUG -O2 -g
CFLAGS_DEBUG   = $(DEFINES) $(FLAGS) $(FLAGS_DEBUG)   -Werror  -Og -g
CFLAGS_PROFILE = $(DEFINES) $(FLAGS) $(FLAGS_PROFILE) -DNDEBUG -O2 -g -pg

LIBS = -L$(libdir) \
	-lboost_date_time \
	-lboost_filesystem \
	-lboost_thread \
	-lboost_regex \
	-lboost_system \
	$(pkg-config --libs icu-i18n) \
	-lfmt \
	-lctpp2 \
	-lgdal \
	-ljpeg \
	-lpng \
	-lpthread -lrt
#	-lopenjpeg \

# What to install

LIBFILE = libsmartmet-$(SUBNAME).so

# How to install

INSTALL_PROG = install -p -m 775
INSTALL_DATA = install -p -m 664

# Compile option overrides

ifneq (,$(findstring debug,$(MAKECMDGOALS)))
  CFLAGS = $(CFLAGS_DEBUG)
endif

ifneq (,$(findstring profile,$(MAKECMDGOALS)))
  CFLAGS = $(CFLAGS_PROFILE)
endif

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
			src/identification
			
vpath %.h 	src \
			src/common \
			src/grid \
			src/grib1 \
			src/grib1/definition \
			src/grib1/implementation \
			src/grib2 \
			src/grib2/definition \
			src/grib2/implementation \
			src/identification

vpath %.o obj



# The files to be compiled

SRCS     = $(patsubst src/%,%,$(wildcard src/*.cpp src/*/*.cpp src/*/definition/*.cpp src/*/implementation/*.cpp))
OBJS     = $(SRCS:%.cpp=%.o)
OBJFILES = $(OBJS:%.o=obj/%.o)

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
	$(CXX) $(CFLAGS) -shared -rdynamic -o $(LIBFILE) $(OBJFILES) $(LIBS)

clean: 
	rm -f src/*~ src/*/*~ src/*/*/*~
	rm -rf obj
	rm -rf $(LIBFILE)

format:
	clang-format -i -style=file $(SUBNAME)/*.h $(SUBNAME)/*.cpp test/*.cpp

install:
	@mkdir -p $(includedir)/$(INCDIR)
	@rm -rf $(includedir)/$(INCDIR)/*
	@mkdir -p $(includedir)/$(INCDIR)/common
	@mkdir -p $(includedir)/$(INCDIR)/grid
	@mkdir -p $(includedir)/$(INCDIR)/grib1
	@mkdir -p $(includedir)/$(INCDIR)/grib1/definition
	@mkdir -p $(includedir)/$(INCDIR)/grib1/implementation
	@mkdir -p $(includedir)/$(INCDIR)/grib2
	@mkdir -p $(includedir)/$(INCDIR)/grib2/definition
	@mkdir -p $(includedir)/$(INCDIR)/grib2/implementation
	@mkdir -p $(includedir)/$(INCDIR)/identification
	@cp src/common/*.h $(includedir)/$(INCDIR)/common
	@cp src/grid/*.h $(includedir)/$(INCDIR)/grid
	@cp src/grib1/*.h $(includedir)/$(INCDIR)/grib1
	@cp src/grib1/definition/*.h $(includedir)/$(INCDIR)/grib1/definition
	@cp src/grib1/implementation/*.h $(includedir)/$(INCDIR)/grib1/implementation
	@cp src/grib2/*.h $(includedir)/$(INCDIR)/grib2
	@cp src/grib2/definition/*.h $(includedir)/$(INCDIR)/grib2/definition
	@cp src/grib2/implementation/*.h $(includedir)/$(INCDIR)/grib2/implementation
	@cp src/identification/*.h $(includedir)/$(INCDIR)/identification	
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
	          obj/identification

create_def:
	cd src/grib1/definition; $(MAKE) definitions;
	cd src/grib2/definition; $(MAKE) definitions;

delete_def:
	cd src/grib1/definition; $(MAKE) clean;
	cd src/grib2/definition; $(MAKE) clean;


rpm: clean
	if [ -e $(SPEC).spec ]; \
	then \
	  tar -czvf $(SPEC).tar.gz --transform "s,^,$(SPEC)/," * ; \
	  rpmbuild -ta $(SPEC).tar.gz ; \
	  rm -f $(SPEC).tar.gz ; \
	else \
	  echo $(SPEC).spec file missing; \
	fi;

.SUFFIXES: $(SUFFIXES) .cpp


obj/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c -o $@ $<

ifneq ($(wildcard obj/*.d),)
-include $(wildcard obj/*.d)
endif
