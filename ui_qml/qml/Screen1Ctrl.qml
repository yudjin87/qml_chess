import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Column {
    FileDialog {
        id: fileOpenDialog
        title: qsTr("Choose chess file to load:")
        folder: "."
        selectExisting: true
        nameFilters: [ "QML Chess files (*.chess)", "All files (*)" ]
        onAccepted: {
            game.load(fileOpenDialog.fileUrl)
            screenStateChart.state = "screen3Ctrl"
        }
    }

    spacing: 4

    Button {
        id: startButton
        text: qsTr("Start new game")
        onClicked: {
            game.start();
            screenStateChart.state = "screen2Ctrl"
        }
    }
    Button {
        id: loadButton
        visible: !game.isRunning;

        text: qsTr("Load")
        onClicked: {
            fileOpenDialog.open()
        }
    }
}
