import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: chessBoard.size()
    width: 800
    height: 480
    visible: true

    ChessBoard {
        id: board
        height: parent.height
        width: board.height
    }
}
