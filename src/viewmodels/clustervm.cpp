#include "clustervm.h"

#include <QtGlobal>

ClusterViewModel::ClusterViewModel(VehicleData *vehicleData, QObject *parent)
    : QObject(parent)
    , m_vehicleData(vehicleData)
{
    // Whenever the Model's raw speed changes, our derived display text is
    // stale and must be recomputed + re-announced to the View. This one
    // connection is the entire "reactivity chain" for Stage 1:
    //
    //   VehicleData::speedKmhChanged()
    //        -> ClusterViewModel::speedDisplayTextChanged()
    //             -> QML Text binding re-evaluates automatically
    connect(m_vehicleData, &VehicleData::speedKmhChanged,
            this, &ClusterViewModel::speedDisplayTextChanged);
}

// This is the ViewModel "transformation" in action: rounding the raw
// double and appending a unit label is presentation logic, which belongs
// here — not in the Model (which shouldn't know about display units) and
// not in the View (QML shouldn't do numeric formatting logic).
QString ClusterViewModel::speedDisplayText() const
{
    const int rounded = qRound(m_vehicleData->speedKmh());
    return QString("%1 km/h").arg(rounded);
}
