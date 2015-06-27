import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: chessBoard.size()
    width: 800
    height: 480
    visible: true

    onClosing: {
        game.stop();
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Column {
            id: buttons
            spacing: 4
            Button {
                id: startButton
                anchors.left: parent.left
                anchors.right: parent.right
                text: game.isRunning ? qsTr("Stop") : qsTr("Start")
                onClicked: {
                    if (game.isRunning)
                        game.stop();
                    else
                        game.start(chessBoard);
                }
            }
            Button {
                id: loadButton
                anchors.left: parent.left
                anchors.right: parent.right
                //enabled: !chessController.gameRunning
                enabled: false

                text: qsTr("Load")
//                onClicked: {
//                    fileOpenDialog.open()
//                }
            }
            Label {
                text: qsTr("Enter file name to save:")
            }

            TextField {
                anchors.left: parent.left
                anchors.right: parent.right
                id: saveFileName
            }

            Button {
                id: saveButton
                anchors.left: parent.left
                anchors.right: parent.right
                //enabled: !chessController.gameRunning && chessController.movesNumber > 0
                enabled: true
                text: qsTr("Save")
//                onClicked: {
//                    if (saveFileName.text != "")
//                        chessController.saveGame(saveFileName.text)
//                }
            }
            Row {
                id: gameControls
                anchors.left: parent.left
                anchors.right: parent.right
                visible: false
                Button {
                    id: prevButton
                    text: "<<"
//                    onClicked: {
//                        chessController.prevMove()
//                    }
                }
                Button {
                    id: nextButton
                    text: ">>"
//                    onClicked: {
//                        chessController.nextMove()
//                    }
                }
            }
        }

        ChessBoard {
            id: board
            height: parent.height
            width: board.height
            anchors.right: parent.right
        }

    }
}
