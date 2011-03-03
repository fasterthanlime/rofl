CONFIG += qt

SOURCES += source/main.cpp source/SKNLoader.cpp source/SKLLoader.cpp source/ddslib/DdsImage.cpp source/ddslib/s3tc.cpp
INCLUDEPATH += ../irrlicht-1.7.2/include
LIBS += -lIrrlicht

TARGET = rofl
DESTDIR = bin
OBJECTS_DIR = .objects

