import QtQuick 2.4

Item {
    id: root
    property int cellSize: width / 8

    Grid {
        id: boardGrid
        anchors.fill: parent;
        property int cellSize: parent.cellSize;
        rows: 8
        columns: 8

        Repeater {
            id: repeater
            model: 64
            Item {
                id: item
                width: root.cellSize;
                height: root.cellSize;

                Rectangle {
                    id: chessCell
                    anchors.fill: parent
                    color: ((Math.floor(index / 8) % 2) === 0)
                           ? (index % 2  === 1 ? "#D18B47" : "#FFCE9E") // light brown &
                           : (index % 2  === 0 ? "#D18B47" : "#FFCE9E") // dark brown
                    border.color: "black";
                    border.width: 1
                }

            }
        }
    }
}
