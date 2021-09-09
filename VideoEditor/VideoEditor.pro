QT += core quick multimedia

CONFIG += c++17
CONFIG -= flat

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/PLL/BLLContext.cpp \
        src/PLL/DelegateTimer.cpp \
        src/BLL/FilesystemPathUtils.cpp \
        src/BLL/ThumbnailGenerator.cpp \
        src/PLL/ThumbnailGeneratorInterface.cpp \
        src/PLL/ThumbnailGeneratorWorker.cpp \
        src/PLL/VideoEffectImageProvider.cpp \
        src/BLL/VideoProcessor/Const.cpp \
        src/BLL/VideoProcessor/ImageEffect/AbstractRandomizableVideoEffect.cpp \
        src/BLL/VideoProcessor/ImageEffect/CircleImageEffectProvider.cpp \
        src/BLL/VideoProcessor/ImageEffect/AbstractVideoEffect.cpp \
        src/BLL/VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.cpp \
        src/BLL/VideoProcessor/ImageEffect/ProgressBarVideoEffect.cpp \
        src/BLL/VideoProcessor/ImageEffect/VideoEffectApplier.cpp \
        src/BLL/VideoProcessor/ImageEffect/VideoEffectApplierEntry.cpp \
        src/BLL/VideoProcessor/VideoProcessorUtils.cpp \
        src/BLL/VideoProcessor/VideoThumbnailProvider.cpp \
        src/PLL/VideoProcessorInterface.cpp \
        src/PLL/VideoProcessorWorker.cpp \
        main.cpp

HEADERS += \
    src/PLL/BLLContext.hpp \
    src/PLL/DelegateTimer.hpp \
    src/BLL/FilesystemPathUtils.hpp \
    src/BLL/ThumbnailGenerator.hpp \
    src/PLL/ThumbnailGeneratorInterface.hpp \
    src/PLL/ThumbnailGeneratorWorker.hpp \
    src/PLL/VideoEffectImageProvider.hpp \
    src/BLL/VideoProcessor/Const.hpp \
    src/BLL/VideoProcessor/ImageEffect/AbstractRandomizableVideoEffect.hpp \
    src/BLL/VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp \
    src/BLL/VideoProcessor/ImageEffect/AbstractVideoEffect.hpp \
    src/BLL/VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.hpp \
    src/BLL/VideoProcessor/ImageEffect/ProgressBarVideoEffect.hpp \
    src/BLL/VideoProcessor/ImageEffect/VideoEffectApplier.hpp \
    src/BLL/VideoProcessor/ImageEffect/VideoEffectApplierEntry.hpp \
    src/BLL/VideoProcessor/VideoProcessorUtils.hpp \
    src/BLL/VideoProcessor/VideoThumbnailProvider.hpp \
    src/PLL/VideoProcessorInterface.hpp \
    src/PLL/VideoProcessorWorker.hpp

INCLUDEPATH += $$PWD/ThirdParty/lib/include
INCLUDEPATH += $$PWD/src
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

# OpenCV-Core
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_core453
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_core453d

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_core453.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_core453d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_core453.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_core453d.lib

unix:!macx: LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

# OpenCV-Imgproc
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_imgproc453
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_imgproc453d

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_imgproc453.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_imgproc453d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_imgproc453.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_imgproc453d.lib

#OpenCV-Imgcodecs
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_imgcodecs453
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_imgcodecs453d

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_imgcodecs453.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_imgcodecs453d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_imgcodecs453.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_imgcodecs453d.lib

#OpenCV-VideoIO
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_videoio453
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_videoio453d

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_videoio453.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/libopencv_videoio453d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_videoio453.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ThirdParty/lib/opencv_videoio453d.lib

unix:!macx: LIBS += -L$$PWD/ThirdParty/lib/ -lopencv_videoio
