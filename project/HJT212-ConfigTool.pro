#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T16:00:38
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE = HJT212-ConfigTool.rc

TARGET = HJT212-ConfigTool
TEMPLATE = app

RESOURCES += ../resource/resource.qrc

SOURCES += ../source/main.cpp\
    ../source/graphical/mainwindow.cpp \
    ../source/graphical/useractions.cpp \
    ../source/graphical/userpopupmenu.cpp \
    ../source/graphical/userlabel.cpp \
    ../source/graphical/usercombobox.cpp \
    ../source/graphical/usercheckbox.cpp \
    ../source/graphical/userlineedit.cpp \
    ../source/graphical/useripv4edit.cpp \
    ../source/graphical/userportedit.cpp \
    ../source/graphical/usergroupbox.cpp \
    ../source/graphical/userbutton.cpp \
    ../source/graphical/usertimeedit.cpp \
    ../source/graphical/userdatetimeedit.cpp \
    ../source/graphical/usertablewidget.cpp \
    ../source/graphical/userstackedwidget.cpp \
    ../source/graphical/userserveredit.cpp \
    ../source/graphical/userdeviceedit.cpp \
    ../source/graphical/userpollutantedit.cpp \
    ../source/graphical/useraddressedit.cpp \
    ../source/graphical/userpacketfieldedit.cpp \
    ../source/graphical/usercontentfieldedit.cpp \
    ../source/graphical/userframeedit.cpp \
    ../source/graphical/userrunninglog.cpp \
    ../source/graphical/userclientconfig.cpp \
    ../source/graphical/userclientdevice.cpp \
    ../source/graphical/userclientsocketlink.cpp \
    ../source/graphical/userclienthandle.cpp \
    ../source/graphical/userclienttreewidget.cpp \
    ../source/graphical/userserverconfig.cpp \
    ../source/graphical/userserverdeviceconfig.cpp \
    ../source/graphical/userserverlisten.cpp \
    ../source/graphical/userserverdevicelink.cpp \
    ../source/graphical/userserverhandle.cpp \
    ../source/graphical/userservertreewidget.cpp \
    ../source/graphical/usertrayicon.cpp \
    ../source/files/userclientlistfile.cpp \
    ../source/files/userserverlistfile.cpp \
    ../source/files/userclientlogfile.cpp \
    ../source/files/userserverlogfile.cpp \
    ../source/files/usertablefield.cpp \
    ../source/files/userclienttable.cpp \
    ../source/files/userservertable.cpp \
    ../source/files/userdatabase.cpp \
    ../source/files/userdefaultparameter.cpp \
    ../source/files/userclientdatabasefile.cpp \
    ../source/files/userserverdatabasefile.cpp \
    ../source/network/usertcpsocket.cpp \
    ../source/network/usertcpserver.cpp \
    ../source/network/usertcpclient.cpp \
    ../source/protocol/usercontent.cpp \
    ../source/protocol/userpacket.cpp \
    ../source/protocol/userframe.cpp \
    ../source/protocol/userprotocol.cpp \
    ../source/device/userpollutant.cpp \
    ../source/device/usermanage.cpp \
    ../source/device/userdevice.cpp \
    ../source/analyzer/useranalyzer.cpp
 
HEADERS  += ../source/Graphical/mainwindow.h \
    ../source/graphical/useractions.h \
    ../source/graphical/userpopupmenu.h \
    ../source/graphical/userlabel.h \
    ../source/graphical/usercombobox.h \
    ../source/graphical/usercheckbox.h \
    ../source/graphical/userlineedit.h \
    ../source/graphical/useripv4edit.h \
    ../source/graphical/userportedit.h \
    ../source/graphical/usergroupbox.h \
    ../source/graphical/userbutton.h \
    ../source/graphical/usertimeedit.h \
    ../source/graphical/userdatetimeedit.h \
    ../source/graphical/usertablewidget.h \
    ../source/graphical/userstackedwidget.h \
    ../source/graphical/userserveredit.h \
    ../source/graphical/userdeviceedit.h \
    ../source/graphical/userpollutantedit.h \
    ../source/graphical/useraddressedit.h \
    ../source/graphical/userpacketfieldedit.h \
    ../source/graphical/usercontentfieldedit.h \
    ../source/graphical/userframeedit.h \
    ../source/graphical/userrunninglog.h \
    ../source/graphical/userclientconfig.h \
    ../source/graphical/userclientdevice.h \
    ../source/graphical/userclientsocketlink.h \
    ../source/graphical/userclienthandle.h \
    ../source/graphical/userclienttreewidget.h \
    ../source/graphical/userserverconfig.h \
    ../source/graphical/userserverdeviceconfig.h \
    ../source/graphical/userserverlisten.h \
    ../source/graphical/userserverdevicelink.h \
    ../source/graphical/userserverhandle.h \
    ../source/graphical/userservertreewidget.h \
    ../source/graphical/usertrayicon.h \
    ../source/files/userclientlistfile.h \
    ../source/files/userserverlistfile.h \
    ../source/files/userclientlogfile.h \
    ../source/files/userserverlogfile.h \
    ../source/files/usertablefield.h \
    ../source/files/userclienttable.h \
    ../source/files/userservertable.h \
    ../source/files/userdatabase.h \
    ../source/files/userdefaultparameter.h \
    ../source/files/userserverdatabasefile.h \
    ../source/files/userclientdatabasefile.h \
    ../source/network/usertcpsocket.h \
    ../source/network/usertcpserver.h \
    ../source/network/usertcpclient.h \
    ../source/protocol/usercontent.h \
    ../source/protocol/userpacket.h \
    ../source/protocol/userframe.h \
    ../source/protocol/userprotocol.h \
    ../source/device/userpollutant.h \
    ../source/device/usermanage.h \
    ../source/device/userdevice.h \
    ../source/analyzer/useranalyzer.h

DISTFILES += \
    readme.txt
