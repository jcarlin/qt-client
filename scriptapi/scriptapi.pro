include( ../global.pri )
TARGET = xtuplescriptapi
TEMPLATE = lib
CONFIG += qt \
    warn_on \
    staticlib
DBFILE = scriptapi.db
LANGUAGE = C++
DEPENDPATH += . \
    ../common \
    ../widgets \
    ../widgets/tmp/lib
INCLUDEPATH += . \
    ../common \
    ../widgets \
    ../widgets/tmp/lib \
    .
DESTDIR = ../lib
MOC_DIR = tmp
OBJECTS_DIR = tmp
UI_DIR = tmp
HEADERS += setupscriptapi.h \
    include.h \
    metasqlhighlighterproto.h \
    orreportproto.h \
    parameterlistsetup.h \
    qactionproto.h \
    qboxlayoutproto.h \
    qbytearrayproto.h \
    qdialogsetup.h \
    qdomattrproto.h \
    qdomcdatasectionproto.h \
    qdomcharacterdataproto.h \
    qdomcommentproto.h \
    qdomdocumentfragmentproto.h \
    qdomdocumentproto.h \
    qdomdocumenttypeproto.h \
    qdomelementproto.h \
    qdomentityproto.h \
    qdomentityreferenceproto.h \
    qdomimplementationproto.h \
    qdomnamednodemapproto.h \
    qdomnodelistproto.h \
    qdomnodeproto.h \
    qdomnotationproto.h \
    qdomprocessinginstructionproto.h \
    qdomtextproto.h \
    qdoublevalidatorproto.h \
    qeventproto.h \
    qfontproto.h \
    qgridlayoutproto.h \
    qiconproto.h \
    qitemdelegateproto.h \
    qlayoutproto.h \
    qlayoutitemproto.h \
    qmenuproto.h \
    qmessageboxsetup.h \
    qnetworkreplyproto.h \
    qnetworkrequestproto.h \
    qprinterproto.h \
    qsizepolicyproto.h \
    qspaceritemproto.h \
    qsqldatabaseproto.h \
    qsqlerrorproto.h \
    qsqlrecordproto.h \
    qstackedwidgetproto.h \
    qtabwidgetproto.h \
    qtextdocumentproto.h \
    qtexteditproto.h \
    qtimerproto.h \
    qtoolbarproto.h \
    qtreewidgetitemproto.h \
    qtsetup.h \
    qurlproto.h \
    qvalidatorproto.h \
    qwidgetproto.h \
    xdatawidgetmapperproto.h \
    xnetworkaccessmanager.h \
    xsqltablemodelproto.h \
    xsqlqueryproto.h \
    addressclustersetup.h \
    alarmssetup.h \
    clineeditsetup.h \
    commentssetup.h \
    contactwidgetsetup.h \
    crmacctlineeditsetup.h \
    currdisplaysetup.h \
    documentssetup.h \
    glclustersetup.h \
    itemlineeditsetup.h \
    orderlineeditsetup.h \
    parametereditproto.h \
    parametergroupsetup.h \
    polineeditsetup.h \
    projectlineeditsetup.h \
    ralineeditsetup.h \
    revisionlineeditsetup.h \
    screensetup.h \
    shipmentclusterlineeditsetup.h \
    solineeditsetup.h \
    tolineeditsetup.h \
    vendorgroupsetup.h \
    wcomboboxsetup.h \
    womatlclustersetup.h \
    xdateeditsetup.h \
    xsqltablenodeproto.h
SOURCES += setupscriptapi.cpp \
    include.cpp \
    metasqlhighlighterproto.cpp \
    orreportproto.cpp \
    parameterlistsetup.cpp \
    qactionproto.cpp \
    qboxlayoutproto.cpp \
    qbytearrayproto.cpp \
    qdialogsetup.cpp \
    qdomattrproto.cpp \
    qdomcdatasectionproto.cpp \
    qdomcharacterdataproto.cpp \
    qdomcommentproto.cpp \
    qdomdocumentfragmentproto.cpp \
    qdomdocumentproto.cpp \
    qdomdocumenttypeproto.cpp \
    qdomelementproto.cpp \
    qdomentityproto.cpp \
    qdomentityreferenceproto.cpp \
    qdomimplementationproto.cpp \
    qdomnamednodemapproto.cpp \
    qdomnodelistproto.cpp \
    qdomnodeproto.cpp \
    qdomnotationproto.cpp \
    qdomprocessinginstructionproto.cpp \
    qdomtextproto.cpp \
    qdoublevalidatorproto.cpp \
    qeventproto.cpp \
    qfontproto.cpp \
    qgridlayoutproto.cpp \
    qiconproto.cpp \
    qitemdelegateproto.cpp \
    qlayoutitemproto.cpp \
    qlayoutproto.cpp \
    qmenuproto.cpp \
    qmessageboxsetup.cpp \
    qnetworkreplyproto.cpp \
    qnetworkrequestproto.cpp \
    qprinterproto.cpp \
    qsizepolicyproto.cpp \
    qspaceritemproto.cpp \
    qsqldatabaseproto.cpp \
    qsqlerrorproto.cpp \
    qsqlrecordproto.cpp \
    qstackedwidgetproto.cpp \
    qtabwidgetproto.cpp \
    qtextdocumentproto.cpp \
    qtexteditproto.cpp \
    qtimerproto.cpp \
    qtoolbarproto.cpp \
    qtreewidgetitemproto.cpp \
    qtsetup.cpp \
    qurlproto.cpp \
    qvalidatorproto.cpp \
    qwidgetproto.cpp \
    xdatawidgetmapperproto.cpp \
    xnetworkaccessmanager.cpp \
    xsqltablemodelproto.cpp \
    xsqlqueryproto.cpp \
    addressclustersetup.cpp \
    alarmssetup.cpp \
    clineeditsetup.cpp \
    commentssetup.cpp \
    contactwidgetsetup.cpp \
    crmacctlineeditsetup.cpp \
    currdisplaysetup.cpp \
    documentssetup.cpp \
    glclustersetup.cpp \
    itemlineeditsetup.cpp \
    orderlineeditsetup.cpp \
    parametereditproto.cpp \
    parametergroupsetup.cpp \
    polineeditsetup.cpp \
    projectlineeditsetup.cpp \
    ralineeditsetup.cpp \
    revisionlineeditsetup.cpp \
    screensetup.cpp \
    shipmentclusterlineeditsetup.cpp \
    solineeditsetup.cpp \
    tolineeditsetup.cpp \
    vendorgroupsetup.cpp \
    wcomboboxsetup.cpp \
    womatlclustersetup.cpp \
    xdateeditsetup.cpp \
    xsqltablnodeproto.cpp
QT += sql \
    xml \
    script \
    network
