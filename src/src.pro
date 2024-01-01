QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddOperatorButton.cpp \
    CountriesOperatorsModel.cpp \
    OperatorEditor.cpp \
    OperatorEditorDialog.cpp \
    TreeIconTextDelegate.cpp \
    TreeItem.cpp \
    TreeItemTypes.cpp \
    main.cpp \
    CountriesListWidget.cpp

HEADERS += \
    AddOperatorButton.hpp \
    CountriesListWidget.hpp \
    CountriesOperatorsModel.hpp \
    OperatorEditor.hpp \
    OperatorEditorDialog.hpp \
    TreeIconTextDelegate.hpp \
    TreeItem.hpp \
    TreeItemTypes.hpp

FORMS += \
    CountriesListWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
