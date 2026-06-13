import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

Window {
    width: 1280
    height: 720
    visible: true
    title: "NovaCockpit - HMI Dashboard"
    color: "#121212"

    // Vòng tròn đồng hồ tốc độ
    Rectangle {
        id: speedGauge
        anchors.centerIn: parent
        width: 400
        height: 400
        radius: 200
        color: "transparent"
        //border.color: "#00ffcc"
        //border.width: 10

        Column {
            anchors.centerIn: parent
            spacing: 5

            Text {
                id: speedText
                // Use Math.round() to hide decimal values during animation
                text: Math.round(speedGauge.animatedSpeed).toString()
                font.pixelSize: 140
                font.bold: true
                color: "#00ffcc"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "km/h"
                font.pixelSize: 32
                color: "#ffffff"
                opacity: 0.7
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        // Custom numeric property to handle smooth interpolation
        property real animatedSpeed: vehicleProvider.speed

        // Correctly animate the numeric property
        Behavior on animatedSpeed {
            NumberAnimation {
                duration: 150
                easing.type: Easing.OutQuad // Smooth deceleration
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (vehicleProvider.speed < 240) {
                    vehicleProvider.speed += 5;
                } else {
                    vehicleProvider.speed = 0;
                }
            }
        }

        // Draw the dynamic speed arc
        Shape {
            anchors.fill: parent
            // Enable anti-aliasing for smooth curves
            layer.enabled: true
            layer.samples: 8

            ShapePath {
                fillColor: "transparent"
                strokeColor: "#00ffcc" // Neon color
                strokeWidth: 15
                capStyle: ShapePath.RoundCap // Rounded ends for the arc

                PathAngleArc {
                    centerX: speedGauge.width / 2
                    centerY: speedGauge.height / 2
                    radiusX: (speedGauge.width / 2) - 20
                    radiusY: (speedGauge.height / 2) - 20

                    // Dashboard standard: start from bottom-left
                    startAngle: 135

                    // Calculate sweep angle dynamically based on max speed (e.g., 240 km/h)
                    // Total circle is 360, we use 270 degrees for the gauge
                    sweepAngle: (speedGauge.animatedSpeed / 120) * 270
                }
            }
        }
        // Display RPM value below the speed gauge
        Text {
            id: rpmText
            anchors.top: speedGauge.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20

            // Bind directly to the C++ rpm property
            text: vehicleProvider.rpm !== undefined ? vehicleProvider.rpm.toString() + " RPM" : "0 RPM"
            font.pixelSize: 40
            color: "#ffffff"
            opacity: 0.8
        }
    }

    Text {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 30
        text: "Click vào đồng hồ để tăng tốc độ"
        color: "#ffffff"
        font.pixelSize: 20
        opacity: 0.5
    }

    Connections {
        target: vehicleProvider

        // DEBUG: Triggered every time speedChanged() is emitted
        // function onSpeedChanged() {
        //     console.log("[QML] Received speed:", vehicleProvider.speed)
        // }
    }
    Row {
        id: gearSelector
        spacing: 25
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        Text {
            text: "P"
            font.pixelSize: 36
            font.bold: true
            font.family: "Ubuntu"

            color: vehicleProvider.currentGear === 0 ? "#00ffcc" : "#333333"
            Behavior on color { ColorAnimation { duration: 200 } }
        }

        Text {
            text: "R"
            font.pixelSize: 36
            font.bold: true
            font.family: "Ubuntu"

            color: vehicleProvider.currentGear === 1 ? "#ff3333" : "#333333"
            Behavior on color { ColorAnimation { duration: 200 } }
        }

        Text {
            text: "N"
            font.pixelSize: 36
            font.bold: true
            font.family: "Ubuntu"

            color: vehicleProvider.currentGear === 2 ? "#ffcc00" : "#333333"
            Behavior on color { ColorAnimation { duration: 200 } }
        }

        Text {
            text: "D"
            font.pixelSize: 36
            font.bold: true
            font.family: "Ubuntu"

            color: vehicleProvider.currentGear === 3 ? "#00ffcc" : "#333333"
            Behavior on color { ColorAnimation { duration: 200 } }
        }
    }
}


