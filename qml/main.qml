import QtQuick
import QtQuick.Window

// =========================================================================
// main.qml  (VIEW layer — Stage 1)
//
// This window contains no logic of its own. It only *binds* to
// properties exposed by clusterVM (the ClusterViewModel instance
// injected from main.cpp via setContextProperty). That is the entire
// contract of the View layer in this architecture: display what the
// ViewModel gives it, react to nothing else.
//
// From Stage 3 onward this file becomes a thin shell that loads
// views/ClassicView.qml or views/SpeedoOnlyView.qml; for now it just
// shows the raw speed text to prove the binding chain is alive.
// =========================================================================
Window {
    id: root

    width: 480
    height: 320
    visible: true
    title: qsTr("MotoCluster — Stage 1")

    color: "#101014"

    Text {
        anchors.centerIn: parent

        // This single binding is Stage 1's proof of concept: every time
        // VehicleData.speedKmh changes, ClusterViewModel recomputes
        // speedDisplayText and emits speedDisplayTextChanged(), and QML's
        // binding engine updates this Text automatically -- no manual
        // signal/slot wiring required on the QML side at all.
        text: clusterVM.speedDisplayText

        color: "#f2f2f2"
        font.pixelSize: 48
        font.family: "sans-serif"
    }
}
