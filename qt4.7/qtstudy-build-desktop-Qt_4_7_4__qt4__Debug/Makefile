#############################################################################
# Makefile for building: qtstudy
# Generated by qmake (2.01a) (Qt 4.7.4) on: Thu Aug 11 10:07:04 2016
# Project:  ../qtstudy/qtstudy.pro
# Template: app
# Command: /opt/qt4/bin/qmake -spec /opt/qt-4.7.4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile ../qtstudy/qtstudy.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/qt-4.7.4/mkspecs/linux-g++-64 -I../qtstudy -I/opt/qt-4.7.4/include/QtCore -I/opt/qt-4.7.4/include/QtGui -I/opt/qt-4.7.4/include -I. -I. -I../qtstudy -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-rpath,/usr/local/Trolltech/Qt-4.7.4/lib
LIBS          = $(SUBLIBS)  -L/opt/qt4/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /opt/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../qtstudy/main.cpp \
		../qtstudy/mainwindow.cpp \
		../qtstudy/combobox.cpp \
		../qtstudy/filedialog.cpp \
		../qtstudy/models/standardmodel.cpp moc_mainwindow.cpp \
		moc_filedialog.cpp
OBJECTS       = main.o \
		mainwindow.o \
		combobox.o \
		filedialog.o \
		standardmodel.o \
		moc_mainwindow.o \
		moc_filedialog.o
DIST          = /opt/qt-4.7.4/mkspecs/common/g++.conf \
		/opt/qt-4.7.4/mkspecs/common/unix.conf \
		/opt/qt-4.7.4/mkspecs/common/linux.conf \
		/opt/qt-4.7.4/mkspecs/qconfig.pri \
		/opt/qt-4.7.4/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt-4.7.4/mkspecs/features/qt_functions.prf \
		/opt/qt-4.7.4/mkspecs/features/qt_config.prf \
		/opt/qt-4.7.4/mkspecs/features/exclusive_builds.prf \
		/opt/qt-4.7.4/mkspecs/features/default_pre.prf \
		/opt/qt-4.7.4/mkspecs/features/debug.prf \
		/opt/qt-4.7.4/mkspecs/features/default_post.prf \
		/opt/qt-4.7.4/mkspecs/features/warn_on.prf \
		/opt/qt-4.7.4/mkspecs/features/qt.prf \
		/opt/qt-4.7.4/mkspecs/features/unix/thread.prf \
		/opt/qt-4.7.4/mkspecs/features/moc.prf \
		/opt/qt-4.7.4/mkspecs/features/resources.prf \
		/opt/qt-4.7.4/mkspecs/features/uic.prf \
		/opt/qt-4.7.4/mkspecs/features/yacc.prf \
		/opt/qt-4.7.4/mkspecs/features/lex.prf \
		/opt/qt-4.7.4/mkspecs/features/include_source_dir.prf \
		../qtstudy/qtstudy.pro
QMAKE_TARGET  = qtstudy
DESTDIR       = 
TARGET        = qtstudy

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ../qtstudy/qtstudy.pro  /opt/qt-4.7.4/mkspecs/linux-g++-64/qmake.conf /opt/qt-4.7.4/mkspecs/common/g++.conf \
		/opt/qt-4.7.4/mkspecs/common/unix.conf \
		/opt/qt-4.7.4/mkspecs/common/linux.conf \
		/opt/qt-4.7.4/mkspecs/qconfig.pri \
		/opt/qt-4.7.4/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt-4.7.4/mkspecs/features/qt_functions.prf \
		/opt/qt-4.7.4/mkspecs/features/qt_config.prf \
		/opt/qt-4.7.4/mkspecs/features/exclusive_builds.prf \
		/opt/qt-4.7.4/mkspecs/features/default_pre.prf \
		/opt/qt-4.7.4/mkspecs/features/debug.prf \
		/opt/qt-4.7.4/mkspecs/features/default_post.prf \
		/opt/qt-4.7.4/mkspecs/features/warn_on.prf \
		/opt/qt-4.7.4/mkspecs/features/qt.prf \
		/opt/qt-4.7.4/mkspecs/features/unix/thread.prf \
		/opt/qt-4.7.4/mkspecs/features/moc.prf \
		/opt/qt-4.7.4/mkspecs/features/resources.prf \
		/opt/qt-4.7.4/mkspecs/features/uic.prf \
		/opt/qt-4.7.4/mkspecs/features/yacc.prf \
		/opt/qt-4.7.4/mkspecs/features/lex.prf \
		/opt/qt-4.7.4/mkspecs/features/include_source_dir.prf \
		/opt/qt4/lib/libQtGui.prl \
		/opt/qt4/lib/libQtCore.prl
	$(QMAKE) -spec /opt/qt-4.7.4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile ../qtstudy/qtstudy.pro
/opt/qt-4.7.4/mkspecs/common/g++.conf:
/opt/qt-4.7.4/mkspecs/common/unix.conf:
/opt/qt-4.7.4/mkspecs/common/linux.conf:
/opt/qt-4.7.4/mkspecs/qconfig.pri:
/opt/qt-4.7.4/mkspecs/modules/qt_webkit_version.pri:
/opt/qt-4.7.4/mkspecs/features/qt_functions.prf:
/opt/qt-4.7.4/mkspecs/features/qt_config.prf:
/opt/qt-4.7.4/mkspecs/features/exclusive_builds.prf:
/opt/qt-4.7.4/mkspecs/features/default_pre.prf:
/opt/qt-4.7.4/mkspecs/features/debug.prf:
/opt/qt-4.7.4/mkspecs/features/default_post.prf:
/opt/qt-4.7.4/mkspecs/features/warn_on.prf:
/opt/qt-4.7.4/mkspecs/features/qt.prf:
/opt/qt-4.7.4/mkspecs/features/unix/thread.prf:
/opt/qt-4.7.4/mkspecs/features/moc.prf:
/opt/qt-4.7.4/mkspecs/features/resources.prf:
/opt/qt-4.7.4/mkspecs/features/uic.prf:
/opt/qt-4.7.4/mkspecs/features/yacc.prf:
/opt/qt-4.7.4/mkspecs/features/lex.prf:
/opt/qt-4.7.4/mkspecs/features/include_source_dir.prf:
/opt/qt4/lib/libQtGui.prl:
/opt/qt4/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /opt/qt-4.7.4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile ../qtstudy/qtstudy.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qtstudy1.0.0 || $(MKDIR) .tmp/qtstudy1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qtstudy1.0.0/ && $(COPY_FILE) --parents ../qtstudy/mainwindow.h ../qtstudy/combobox.h ../qtstudy/filedialog.h ../qtstudy/models/standardmodel.h .tmp/qtstudy1.0.0/ && $(COPY_FILE) --parents ../qtstudy/main.cpp ../qtstudy/mainwindow.cpp ../qtstudy/combobox.cpp ../qtstudy/filedialog.cpp ../qtstudy/models/standardmodel.cpp .tmp/qtstudy1.0.0/ && $(COPY_FILE) --parents ../qtstudy/mainwindow.ui .tmp/qtstudy1.0.0/ && (cd `dirname .tmp/qtstudy1.0.0` && $(TAR) qtstudy1.0.0.tar qtstudy1.0.0 && $(COMPRESS) qtstudy1.0.0.tar) && $(MOVE) `dirname .tmp/qtstudy1.0.0`/qtstudy1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qtstudy1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_filedialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_filedialog.cpp
moc_mainwindow.cpp: ../qtstudy/mainwindow.h
	/opt/qt4/bin/moc $(DEFINES) $(INCPATH) ../qtstudy/mainwindow.h -o moc_mainwindow.cpp

moc_filedialog.cpp: ../qtstudy/filedialog.h
	/opt/qt4/bin/moc $(DEFINES) $(INCPATH) ../qtstudy/filedialog.h -o moc_filedialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: ../qtstudy/mainwindow.ui
	/opt/qt4/bin/uic ../qtstudy/mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: ../qtstudy/main.cpp ../qtstudy/mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../qtstudy/main.cpp

mainwindow.o: ../qtstudy/mainwindow.cpp ../qtstudy/mainwindow.h \
		ui_mainwindow.h \
		../qtstudy/models/standardmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o ../qtstudy/mainwindow.cpp

combobox.o: ../qtstudy/combobox.cpp ../qtstudy/combobox.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o combobox.o ../qtstudy/combobox.cpp

filedialog.o: ../qtstudy/filedialog.cpp ../qtstudy/filedialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o filedialog.o ../qtstudy/filedialog.cpp

standardmodel.o: ../qtstudy/models/standardmodel.cpp ../qtstudy/models/standardmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o standardmodel.o ../qtstudy/models/standardmodel.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_filedialog.o: moc_filedialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_filedialog.o moc_filedialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

