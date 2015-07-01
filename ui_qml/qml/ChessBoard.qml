import QtQuick 2.4
import ChessUi 1.0


Item {
    function mapIndex(i) {
        var mod8 = i % 8;
        var base = Math.floor(i / 8);
        return 64 - ((base + 1)* 8) + mod8;
    }

//    function repaintBoard() {
//        for (var i = 0; i < 64; ++i) {
//            repeater.itemAt(i).color =
//                    game.board.squareByIdex(mapIndex(i)).color() === 0 ? "#D18B47" : "#FFCE9E"
//        }
//    }

    id: root
    property int cellSize: width / 8

    Connections {
        id: boardConnection
        target: game.board
        onPieceAdded: {
            repeater.itemAt(mapIndex(piece.atSquare().index())).piece = piece
        }

        onPieceRemoved: {
            repeater.itemAt(mapIndex(piece.atSquare().index())).piece = null
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
                property alias color: chessCell.color

                Rectangle {
                    id: chessCell
                    anchors.fill: parent
                    color: game.board.squareByIdex(mapIndex(index)).color() === 0 ? "#D18B47" : "#FFCE9E"
                    border.color: "black";
                    border.width: 1
                }

                PieceItem {
                    id: pieceItem
                    anchors.fill: parent
                }


                Text {
                    id: squareLabel
                    text: index + ": " + game.board.squareByIdex(mapIndex(index)).toStr()
                }

                // transparent item for mouse handle
                Item {
                    anchors.fill: parent
                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            if (!game.isRunning)
                                return;

                            //repaintBoard(); // too expensive

                            var square = game.board.squareByIdex(mapIndex(index));
                            var availableMovements = game.activePlayer.availableMovements;
                            if (availableMovements.contains(square)) {
                                game.activePlayer.moveTo(square);
                                return;
                            }

                            var piece = square.piece();
                            if (!game.activePlayer.selectPiece(piece)) {
                                console.log("onClicked: exit")
                                return;
                            }

                            var moves = game.activePlayer.availableMovements;
                            for (var i = 0; i < moves.length; ++i) {
//                                var m = moves.at(i);
//                                var s = m.square
//                                if (m.type === 0)
//                                    repeater.itemAt(mapIndex(s.index())).color = "#220000FF"
//                                else if (m.type === 1)
//                                    repeater.itemAt(mapIndex(s.index())).color = "#80FF0000"
//                                else if (m.type === 2)
//                                    repeater.itemAt(mapIndex(s.index())).color = "#8000FF00"
//                                else if (m.type === 3)
//                                    repeater.itemAt(mapIndex(s.index())).color = "#80F00F00"
                            }

                        }
                    }
                }

            }
        }
    }
}
