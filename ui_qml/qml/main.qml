import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ChessUi 1.0

ApplicationWindow {
    id: mainWindow
    title: {
        game.activePlayer === null ? "Start game" : game.activePlayer.name;
    }

    width: 800
    height: 480
    visible: true

    onClosing: {
        game.stop();
    }

    MessageDialog {
        id: executionFailedDialog
        title: "Replay failed"
        text: "It's unfair to change saved data and then expect me to continue without any issues"
        icon: StandardIcon.Warning
        onAccepted: {
            console.log("And of course you could only agree.")
        }
        Component.onCompleted: visible = false
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

    Connections {
        id: movesRegistryConnection
        target: game.movesRegistry
        onExecutionFailed: {
            executionFailedDialog.open()
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
                text: game.isRunning ? qsTr("Stop") : qsTr("Start new game")
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

            Label {
                id: saveLabel
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
                enabled: saveFileName.text.length > 0
                text: qsTr("Save")
                onClicked: {
                    if (saveFileName.text != "")
                        game.save(saveFileName.text)
                }
            }

            Row {
                id: gameControls
                anchors.left: parent.left
                anchors.right: parent.right
                visible: false//game.mode === g
                Button {
                    id: prevButton
                    enabled: game.movesRegistry.canUndo
                    text: "Prev"
                    onClicked: {
                        game.movesRegistry.undo()
                    }
                }
                Button {
                    id: nextButton
                    enabled: game.movesRegistry.canRedo
                    text: "Next"
                    onClicked: {
                        game.movesRegistry.redo()
                    }
                }
            }
        }

        ChessboardItem {
            id: board
            height: parent.height
            width: board.height
            anchors.right: parent.right
            chessboard: game.board
        }

//        ChessBoard {
//            id: board
//            height: parent.height
//            width: board.height
//            anchors.right: parent.right
//        }

    }
}
