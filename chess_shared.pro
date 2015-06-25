#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T17:43:40
#
#-------------------------------------------------

CHESS_SOURCE_TREE_ROOT = $$PWD

win32-msvc* {
    QMAKE_CXXFLAGS += /Wall
    QMAKE_CXXFLAGS += /WX
    QMAKE_CXXFLAGS += /wd4350 # xstring(684) : warning C4350: behavior change:...
    QMAKE_CXXFLAGS += /wd4619 # qvector.h(273) : warning C4619: #pragma warning : there is no warning number '4345'
}

INCLUDEPATH += $$CHESS_SOURCE_TREE_ROOT
CONFIG += static # better for tests

#########################################################
# Format binary output path:
win32-g*:BUILD_CONFIG=mingw
win32-msvc*:BUILD_CONFIG=msvc
macx:BUILD_CONFIG=clang
unix:BUILD_CONFIG=gnu

contains(QMAKE_HOST.arch, x86_64) {
    BUILD_CONFIG=$${BUILD_CONFIG}-x64
} else {
    BUILD_CONFIG=$${BUILD_CONFIG}-x32
}

CONFIG(release, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-release
}
CONFIG(debug, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-debug
}

static {# everything below takes effect with CONFIG+=static
    DEFINES += STATIC_BUILD
    BUILD_CONFIG=$${BUILD_CONFIG}-static
} else {
    DEFINES -= STATIC_BUILD
}

BIN_OUTPUT_PATH = $${CHESS_SOURCE_TREE_ROOT}/product/$${BUILD_CONFIG}

DESTDIR         = $${BIN_OUTPUT_PATH}/bin

# Store intermediate stuff somewhere else
OBJECTS_DIR     = $${BIN_OUTPUT_PATH}/intermediate/obj/$${TARGET}
MOC_DIR         = $${BIN_OUTPUT_PATH}/intermediate/moc/$${TARGET}
RCC_DIR         = $${BIN_OUTPUT_PATH}/intermediate/rcc/$${TARGET}
UI_DIR          = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
