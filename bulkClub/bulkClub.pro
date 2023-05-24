QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddMemberDialog.cpp \
    ChangeItemPriceDialog.cpp \
    DeleteItemDialog.cpp \
    DeleteMemberDialog.cpp \
    Employee.cpp \
    ItemAddDialog.cpp \
    datawarehouse.cpp \
    item.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    membersearch.cpp \
    transaction.cpp

HEADERS += \
    AddMemberDialog.h \
    ChangeItemPriceDialog.h \
    Common.h \
    DeleteItemDialog.h \
    DeleteMemberDialog.h \
    Employee.h \
    ItemAddDialog.h \
    datawarehouse.h \
    item.h \
    login.h \
    mainwindow.h \
    member.h \
    membersearch.h \
    transaction.h

FORMS += \
    login.ui \
    mainwindow.ui \
    membersearch.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc \
    image.qrc
