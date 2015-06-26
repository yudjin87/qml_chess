import QtQuick 2.4
import ChessUi 1.0

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
                    property PieceItem piece: chessBoard.pieceByIdex(index)
                    anchors.fill: parent
                    color: chessBoard.squareByIdex(index).color() === 0 ? "#FFCE9E" : "#D18B47"
                    border.color: "black";
                    border.width: 1

                    onPieceChanged: {
                        if (piece != null) {
                            chessCell.children = piece
                            piece.z = 1
                            piece.anchors.fill = chessCell
                            piece.width = chessCell.width
                            piece.height = chessCell.height
                        }
                    }
                }

            }
        }
    }
}
