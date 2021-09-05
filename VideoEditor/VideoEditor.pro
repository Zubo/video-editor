QT += core quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

unix:!macx: INCLUDEPATH += /usr/local/include/opencv4

INCLUDEPATH += $$PWD/ThirdParty/lib/include
DEPENDPATH += $$PWD/ThirdParty/lib/include

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

unix:!macx: LIBS += -lopencv_core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_core453
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_core453d


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_core453.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_core453d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_core453.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_core453d.lib
