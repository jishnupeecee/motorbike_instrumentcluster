#pragma once

#include <QObject>

// =========================================================================
// VehicleData  (MODEL layer)
//
// Role in the MVVM architecture:
//   This class owns the *raw* state of the motorcycle — the numbers that
//   would, in the final system, come off the CAN bus. It knows nothing
//   about QML, gauges, angles, or how anything is displayed.
//
//   In Stage 1 it exposes exactly one property (speedKmh) so we can prove
//   the full Model -> ViewModel -> View data-binding chain works before
//   any real UI is built. Later stages add rpm, fuelLevel, tripDistance,
//   telltale flags, etc. to this same class (or to sibling Model classes
//   such as TelltaleModel / TripComputer).
//
//   Nothing outside this class should ever write these values directly
//   except the input source (the ControlFaceplate simulator today, a CAN
//   bus reader later) — everything else only *reads* via the ViewModel.
// =========================================================================
class VehicleData : public QObject
{
    Q_OBJECT

    // Q_PROPERTY wires this member into Qt's meta-object system so it can
    // be bound to from QML/C++ and emits speedKmhChanged() whenever it's
    // updated — that signal is what drives automatic UI updates.
    Q_PROPERTY(double speedKmh READ speedKmh WRITE setSpeedKmh NOTIFY speedKmhChanged)

public:
    explicit VehicleData(QObject *parent = nullptr);

    double speedKmh() const;
    void setSpeedKmh(double value);

signals:
    void speedKmhChanged();

private:
    double m_speedKmh = 0.0;
};
