#include "vehicledata.h"

#include <algorithm>

VehicleData::VehicleData(QObject *parent)
    : QObject(parent)
{
}

double VehicleData::speedKmh() const
{
    return m_speedKmh;
}

// Setter is intentionally defensive: raw input sources (a slider, a noisy
// CAN signal) can hand us out-of-range or duplicate values. Clamping and
// change-detection belong here in the Model, not scattered across every
// consumer of this data.
void VehicleData::setSpeedKmh(double value)
{
    const double clamped = std::clamp(value, 0.0, 400.0);

    if (qFuzzyCompare(m_speedKmh + 1.0, clamped + 1.0)) // +1.0 avoids 0 vs 0 edge case
        return;

    m_speedKmh = clamped;
    emit speedKmhChanged();
}
