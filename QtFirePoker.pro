QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    main.cpp \
    PokerTextFile.cpp \
    Hand.cpp \
    Card.cpp \
    Player.cpp \
    MainWindow.cpp \
    qcustomplot.cpp \
    HoleCards.cpp

HEADERS += \
    PokerTextFile.h \
    Hand.h \
    Card.h \
    Player.h \
    MainWindow.h \
    qcustomplot.h \
    HoleCards.h
