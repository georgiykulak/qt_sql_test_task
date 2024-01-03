QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ProxyStyle.cpp \
    main.cpp \
    dialog/OperatorEditorDialog.cpp \
    model/CountriesOperatorsModel.cpp \
    model/TreeIconTextDelegate.cpp \
    model/TreeItem.cpp \
    model/TreeItemTypes.cpp \
    view/CountriesListWidget.cpp \
    view/OperatorEditor.cpp \
    view/buttons/AddOperatorButton.cpp \
    view/buttons/OperatorDataButton.cpp \
    view/line_edits/IFieldEdit.cpp \
    view/line_edits/IntFieldEdit.cpp \
    view/line_edits/StringFieldEdit.cpp

HEADERS += \
    ProxyStyle.hpp \
    dialog/OperatorEditorDialog.hpp \
    model/CountriesOperatorsModel.hpp \
    model/TreeIconTextDelegate.hpp \
    model/TreeItem.hpp \
    model/TreeItemTypes.hpp \
    view/CountriesListWidget.hpp \
    view/OperatorEditor.hpp \
    view/buttons/AddOperatorButton.hpp \
    view/buttons/OperatorDataButton.hpp \
    view/line_edits/IFieldEdit.hpp \
    view/line_edits/IntFieldEdit.hpp \
    view/line_edits/StringFieldEdit.hpp

FORMS += \
    CountriesListWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
