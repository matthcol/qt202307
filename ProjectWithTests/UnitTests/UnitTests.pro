QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testmyfunctions.cpp

include(../MyApplication/geometry.pri)

# NB: message to debug .pro
#message("INCLUDEPATH: $$INCLUDEPATH")
#message("PWD: $$PWD")

