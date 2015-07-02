import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

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
        id: movesRegistryConnection
        target: game.movesRegistry
        onExecutionFailed: {
            executionFailedDialog.open()
        }
    }

    Item {
        id: screenStateChart
        state: "screen1Ctrl"
        states: [
            State {
                name: "screen1Ctrl"
                PropertyChanges { target: screen1Ctrl; visible: true; enabled: true; restoreEntryValues: true }
            },

            State {
                name: "screen2Ctrl"
                PropertyChanges { target: screen2Ctrl; visible: true; enabled: true; restoreEntryValues: true }
            },
            State {
                name: "screen3Ctrl"
                PropertyChanges { target: screen3Ctrl; visible: true; enabled: true; restoreEntryValues: true }
            }
        ]
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10

        ColumnLayout {
            anchors.fill: parent
            spacing: 4

            Screen1Ctrl {
                id: screen1Ctrl
                enabled: false
                visible: false
            }

            Screen2Ctrl {
                id: screen2Ctrl
                enabled: false
                visible: false
            }

            Screen3Ctrl {
                id: screen3Ctrl
                enabled: false
                visible: false
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
