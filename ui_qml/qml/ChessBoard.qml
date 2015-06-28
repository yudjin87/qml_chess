import QtQuick 2.4
import ChessUi 1.0


Item {
    function mapIndex(i) {
        var mod8 = i % 8;
        var base = Math.floor(i / 8);
        return 64 - ((base + 1)* 8) + mod8;
    }

    function repaintBoard() {
        for (var i = 0; i < 64; ++i) {
            repeater.itemAt(i).color =
                    game.board.squareByIdex(mapIndex(i)).color() === 0 ? "#D18B47" : "#FFCE9E"
        }
    }

    id: root
    property int cellSize: width / 8

    Connections {
        id: boardConnection
        target: game.board
        onPieceAdded: {
            //console.log("Added: " + piece.atSquare().toStr())
            repeater.itemAt(mapIndex(piece.atSquare().index())).piece = piece
        }

        onPieceRemoved: {
            //console.log("Added: " + piece.atSquare().toStr())
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
//                    property PieceItem pieceItem: null
                    anchors.fill: parent
                    color: game.board.squareByIdex(mapIndex(index)).color() === 0 ? "#D18B47" : "#FFCE9E"
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

                        onEntered: {                            
                        }

                        onExited: {
                        }

                        onClicked: {
                            console.log("onClicked: enter")
                            repaintBoard(); // TODO: too expensive
                            console.log("repaintBoard finished")

                            var square = game.board.squareByIdex(mapIndex(index));
                            var availableMovements = game.activePlayer.availableMovements;
                            if (availableMovements.contains(square)) {
                                game.activePlayer.moveTo(square);
                                console.log("onClicked: exit")
                                return;
                            }

                            var availableAttacks = game.activePlayer.availableAttacks;
                            if (availableAttacks.contains(square)) {
                                game.activePlayer.attack(square);
                                console.log("onClicked: exit")
                                return;
                            }

                            var piece = square.piece();
                            if (piece === null) {
                                console.log("onClicked: exit")
                                return;
                            }

                            if (!game.activePlayer.selectPiece(piece)) {
                                console.log("onClicked: exit")
                                return;
                            }

                            chessCell.color = "#800000FF"
                            var moves = game.activePlayer.availableMovements;
                            //console.log("Hello " + chessBoard.squareByIdex(mapIndex(index)).toStr() + ", " + piece.possibleMoves().length)
                            //console.log("Hello " + moves.length)
                            for (var i = 0; i < moves.length; ++i) {
                                var s = moves.at(i);
                                //console.log("     " + s.toStr());
                                repeater.itemAt(mapIndex(s.index())).color = "#220000FF"
                            }

                            var attacks = game.activePlayer.availableAttacks;
                            for (i = 0; i < attacks.length; ++i) {
                                s = attacks.at(i);
                                repeater.itemAt(mapIndex(s.index())).color = "#80FF0000"
                            }

                        }
                    }
                }

            }
        }
    }
}
