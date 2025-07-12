QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    flight.cpp \
    imageInfo.cpp \
    main.cpp \
    loginwindow.cpp \
    managerlogin.cpp \
    managerwindow.cpp \
    passenger.cpp \
    registerwindow.cpp \
    InfoWindow.cpp \
    checkWindow.cpp \
    homepage.cpp \
    DBOperator.cpp \
    class.cpp \
    customerservicepage.cpp \
    buyticket.cpp \
    ticket.cpp \
    placeorder.cpp \
    detail.cpp

HEADERS += \
    flight.h \
    imageInfo.h \
    loginwindow.h \
    managerlogin.h \
    managerwindow.h \
    passenger.h \
    paymentdialog.h \
    registerwindow.h \
    InfoWindow.h \
    checkWindow.h \
    homepage.h \
    DBOperator.h \
    customerservicepage.h \
    buyticket.h \
    ticket.h \
    placeorder.h \
    detail.h

FORMS += \
    loginwindow.ui \
    managerlogin.ui \
    managerwindow.ui \
    registerwindow.ui \
    InfoWindow.ui \
    checkWindow.ui \
    homepage.ui \
    customerservicepage.ui \
    buyticket.ui \
    placeorder.ui \
    detail.ui \

TRANSLATIONS += \
    FlightProject_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    flight_images.qrc

DISTFILES += \
    ../sign/2exitSign.png \
    ../sign/3exitSign.png \
    ../sign/4exitSign.png \
    ../sign/5exitSign.png
