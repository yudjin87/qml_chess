import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import Chess 1.0

Item {
    id: prevNextButtons
    signal prevClicked
    signal nextClicked

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

    Connections {
        id: movesRegistryConnection
        target: game.movesRegistry
        onExecutionFailed: {
            executionFailedDialog.open()
        }
    }

    Column {

        Button {
            id: stopButton
            text: qsTr("Stop")
            onClicked: {
                game.stop();
                screenStateChart.state = "screen1Ctrl"
            }
        }

        Row {
            id: gameControls
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
}
