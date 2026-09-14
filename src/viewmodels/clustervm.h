#pragma once

#include <QObject>
#include <QString>

#include "../models/vehicledata.h"

// =========================================================================
// ClusterViewModel  (VIEWMODEL layer)
//
// Role in the MVVM architecture:
//   This is the adapter between the raw Model (VehicleData) and the QML
//   View. It never invents state of its own — it *transforms* Model data
//   into display-ready form (formatted strings, rounded values, later:
//   needle angles in degrees, colour states, etc.).
//
//   The View binds ONLY to this class, never to VehicleData directly.
//   That boundary is what lets us change the Model's internal
//   representation (e.g. switch from km/h to raw wheel-speed pulses)
//   without touching a single line of QML.
//
//   Stage 1 exposes one derived property, speedDisplayText, to prove that
//   transformation actually happens (not just a pass-through binding).
// =========================================================================
class ClusterViewModel : public QObject
{
    Q_OBJECT

    // Display-ready text such as "0 km/h" — this is what the View shows.
    // Recomputed and re-emitted whenever the underlying Model changes.
    Q_PROPERTY(QString speedDisplayText READ speedDisplayText NOTIFY speedDisplayTextChanged)

public:
    // The ViewModel does not own the Model — it observes it. Ownership of
    // VehicleData stays in main.cpp, which is where the real data source
    // (faceplate today, CAN reader later) will also plug in.
    explicit ClusterViewModel(VehicleData *vehicleData, QObject *parent = nullptr);

    QString speedDisplayText() const;

signals:
    void speedDisplayTextChanged();

private:
    VehicleData *m_vehicleData = nullptr;
};
