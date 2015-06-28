import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: {
        game.activePlayer === null ? "Start game" : game.activePlayer.name;
    }

    width: 800
    height: 480
    visible: true

    onClosing: {
        game.stop();
    }

    FileDialog {
        id: fileOpenDialog
        title: qsTr("Choose chess file to load:")
        folder: "."
        selectExisting: true
        nameFilters: [ "QML Chess files (*.chess)", "All files (*)" ]
        onAccepted: {
            game.load(fileOpenDialog.fileUrl)
        }
    }

    Connections {
        id: gameConnection
        target: game
        onModeChanged: {
            switch (mode) {
            case 0:
                gameControls.visible = false
                saveLabel.visible = true
                saveButton.visible = true
                saveFileName.visible = true
                break;
            case 1:
                gameControls.visible = true
                saveLabel.visible = false
                saveButton.visible = false
                saveFileName.visible = false
                break;
            }

        }
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
                        game.start();
                }
            }
            Button {
                id: loadButton
                anchors.left: parent.left
                anchors.right: parent.right
                visible: !game.isRunning;

                text: qsTr("Load")
                onClicked: {
                    fileOpenDialog.open()
                }
            }

//            Item {
//                id: saveItem
//                anchors.left: parent.left
//                anchors.right: parent.right
//                visible: ((game.isRunning) && (game.mode === 0))
            Label {
                id: saveLabel
                text: qsTr("Enter file name to save:")
                //visible: game.isRunning
            }

            TextField {
                anchors.left: parent.left
                anchors.right: parent.right
                id: saveFileName
                //visible: game.isRunning
            }

            Button {
                id: saveButton
                //visible: game.isRunning
                anchors.left: parent.left
                anchors.right: parent.right
                //enabled: !chessController.gameRunning && chessController.movesNumber > 0
                enabled: saveFileName.text.length > 0
                text: qsTr("Save")
                onClicked: {
                    if (saveFileName.text != "")
                        game.save(saveFileName.text)
                }
            }
            //}

            Row {
                id: gameControls
                anchors.left: parent.left
                anchors.right: parent.right
                visible: false//game.mode === g
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
