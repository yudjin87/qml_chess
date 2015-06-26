import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: chessBoard.squareByIdex(0).toStr()
    width: 640
    height: 480
    visible: true

    ChessBoard {
        anchors.fill: parent
    }
}