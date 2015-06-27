import QtQuick 2.4
import ChessUi 1.0

Item {

    id: root
    property int cellSize: width / 8

    Connections {
        target: chessBoard
        onPieceAdded: {
            console.log("Added: " + piece.atSquare().toStr())
            repeater.itemAt(piece.atSquare().index()).piece = piece
        }
    }

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
                property alias piece: pieceItem.piece

                Rectangle {
                    id: chessCell
//                    property PieceItem pieceItem: null
                    anchors.fill: parent
                    color: chessBoard.squareByIdex(index).color() === 0 ? "#D18B47" : "#FFCE9E"
                    //color: chessBoard.squareByIdex(index).color() === 0 ? "black" : "white"
                    border.color: "black";
                    border.width: 1

//                    onPieceItemChanged: {
//                        if (pieceItem != null) {
//                            chessCell.children = pieceItem
//                            pieceItem.z = 1
//                            pieceItem.anchors.fill = chessCell
//                            pieceItem.width = chessCell.width
//                            pieceItem.height = chessCell.height
//                        }
//                    }
                }

                PieceItem {
                    id: pieceItem
                    anchors.fill: parent
                }


                Text {
                    function calc() {
                        var i = index;

                        return i;//64 - ((i % 8) + 1) * 8 + (i % 8);
                    }

                    id: tName
                    text: calc() + ": " + chessBoard.squareByIdex(index).toStr()
                }

                //transparent item for mouse handle
                Item {
                    anchors.fill: parent
                    //z: 100
                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            chessCell.color = "red"
                        }

                        onExited: {
                            chessCell.color = chessBoard.squareByIdex(index).color() === 0 ? "#FFCE9E" : "#D18B47"
                        }

                        onClicked: {
                            console.log("Hello" + chessBoard.squareByIdex(index).toStr())
                            game.createGame(chessBoard);
                        }
                    }
                }

            }
        }
    }
}
