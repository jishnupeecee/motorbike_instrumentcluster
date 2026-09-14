#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "models/vehicledata.h"
#include "viewmodels/clustervm.h"

// =========================================================================
// Stage 1 entry point.
//
// Purpose of this stage: prove the full MVVM data path works end to end
// -- Model change -> ViewModel transformation -> View update -- before
// any real gauges or the control faceplate exist.
//
// A QTimer stands in for a real input source here. In Stage 2 this timer
// is deleted and replaced by the ControlFaceplate's speed slider writing
// into VehicleData; in the final system it's replaced by a CAN bus
// reader doing the same thing. The Model/ViewModel/View code above this
// point never needs to know which of the three is driving it.
// =========================================================================
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // --- Model ---
    // Owned on the stack in main(); its lifetime spans the whole app.
    VehicleData vehicleData;

    // --- ViewModel ---
    // Observes vehicleData; owns no data of its own.
    ClusterViewModel clusterViewModel(&vehicleData);

    // --- View ---
    QQmlApplicationEngine engine;

    // Exposing the ViewModel (never the Model) as a context property is
    // what lets qml/main.qml bind to `clusterVM.speedDisplayText`.
    engine.rootContext()->setContextProperty("clusterVM", &clusterViewModel);

    const QUrl url(QStringLiteral("qrc:/qt/qml/MotoCluster/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, [] { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    // --- Dummy reactivity proof (Stage 1 only, removed in Stage 2) ---
    // Ticks the raw Model value once a second so you can watch the
    // on-screen text update with zero manual UI wiring -- proving the
    // Q_PROPERTY/NOTIFY/binding chain is correctly connected.
    QTimer dummyInputTimer;
    QObject::connect(&dummyInputTimer, &QTimer::timeout, &app, [&vehicleData]() {
        double next = vehicleData.speedKmh() + 5.0;
        if (next > 200.0)
            next = 0.0;
        vehicleData.setSpeedKmh(next);
    });
    dummyInputTimer.start(100);

    return app.exec();
}
