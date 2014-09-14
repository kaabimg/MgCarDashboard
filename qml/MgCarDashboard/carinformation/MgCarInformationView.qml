import QtQuick 2.2
import Qt3D 2.0
import Qt3D.Shapes 2.0
import "../utils"



Item {
    id : root



    Viewport {
        id : viewPort

        anchors.fill: parent

        camera: Camera{
            property int scale: 5
            eye.x : 20 * scale
            eye.y : 20 * scale
            eye.z : 20 * scale

        }

        property real lineLenght : 100
        property real lineWidth : 0.1

//        Item3D {
//            position: Qt.vector3d(-viewPort.lineLenght, 0, 0)
//            mesh: CylinderMesh {
//                radius: viewPort.lineWidth
//                length: viewPort.lineLenght
//            }
//            effect: Effect {
//                color: "#aaca00"
//            }
//        }

//        Line {
//            id : xAxis
//            width : viewPort.lineWidth
//            vertices: [
//                0, 0, 0,
//                0, 0, viewPort.lineLenght
//            ]
//            effect: Effect {
//                color: Qt.rgba(1,0,0,1)
//                blending: true
//            }
//        }
//        Line {
//            id : yAxis
//            vertices: [
//                0, 0, 0,
//                0, viewPort.lineLenght, 0
//            ]
//            effect: Effect {
//                color:  Qt.rgba(0,1,0,1)
//                blending: true
//            }
//        }
//        Line {
//            id : zAxis
//            vertices: [
//                0, 0, 0,
//                0, 0, viewPort.lineLenght
//            ]
//            effect: Effect {
//                color: Qt.rgba(0,0,1,1)
//                blending: true
//            }
//        }


//        Quad {
//             scale: 50
//             position: Qt.vector3d(0, 0, 0)
//             effect: Effect {
//                 id: glass
//                 blending: true
//                 color: Qt.rgba(0.7,0.2,0.2,0.5)
//             }
//         }


//        Item3D {
//           mesh :  Mesh {
//                id: carCoreMesh
//                source: "qrc:/resources/3d/prius.obj"

//            }

//            effect: Effect {
//                blending: true;
//                color: Qt.rgba(0.7,0.2,0.2,0.5)
//            }

//            Component.onCompleted: {
//                console.log("Position ",position);
//            }

//        }

    }

}

