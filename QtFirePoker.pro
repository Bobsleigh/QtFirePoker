QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    main.cpp \
    GUI/MainWindow.cpp \
    GUI/qcustomplot.cpp \
    Parsing/Card.cpp \
    Parsing/Hand.cpp \
    Parsing/HoleCards.cpp \
    Parsing/Player.cpp \
    Parsing/PokerTextFile.cpp \
    Parsing/StatsCounter.cpp

HEADERS += \
    GUI/MainWindow.h \
    GUI/qcustomplot.h \
    Parsing/Card.h \
    Parsing/Hand.h \
    Parsing/HoleCards.h \
    Parsing/Player.h \
    Parsing/PokerTextFile.h \
    Parsing/StatsCounter.h
