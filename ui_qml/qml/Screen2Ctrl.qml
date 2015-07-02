import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: stopSaveButtons

    Column {
        spacing: 4

        Button {
            id: stopButton
            text: qsTr("Stop")
            onClicked: {
                game.stop();
                screenStateChart.state = "screen1Ctrl"
            }
        }

        Label {
            id: saveLabel
            text: qsTr("Enter file name to save:")
        }

        TextField {
            id: saveFileName
        }

        Button {
            id: saveButton
            enabled: saveFileName.text.length > 0
            text: qsTr("Save")
            onClicked: {
                if (saveFileName.text != "")
                    game.save(saveFileName.text)
            }
        }
    }
}
