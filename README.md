# MotoCluster — Touring Motorcycle Instrument Cluster (QML/MVVM)

A from-scratch learning project: a Qt6/QML instrument cluster built with
an MVVM architecture, developed in staged milestones.

## Architecture

- **Model** (`src/models/`) — raw vehicle state, no UI knowledge.
- **ViewModel** (`src/viewmodels/`) — adapts Model data into display-ready,
  QML-bindable properties.
- **View** (`qml/`) — pure QML, binds to ViewModels only, contains no
  business logic.

See the code comments in each file — every class explains its role in
this architecture at the top of its header.

## Stage 1 — Skeleton & Wiring (current)

Goal: prove the Model → ViewModel → View binding chain works before any
real gauges exist.

- `VehicleData` (Model): one property, `speedKmh`.
- `ClusterViewModel` (ViewModel): derives `speedDisplayText` from it.
- `main.qml` (View): shows that text.
- A `QTimer` in `main.cpp` fakes an input source, incrementing speed
  every second — this timer is removed in Stage 2 once the real Control
  Faceplate exists.

### Building

Requires Qt 6.5+ with the Quick/Qml modules, and CMake 3.16+.

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64
cmake --build .
./MotoCluster        # (or MotoCluster.exe on Windows)
```

You should see a dark window with a speed readout counting up from
`0 km/h` in steps of 5, wrapping back to 0 past 200 — confirming the
full binding chain is alive with zero manual signal wiring in QML.

## Roadmap

| Stage | Focus | Status |
|---|---|---|
| 1 | Skeleton & MVVM wiring | ✅ done |
| 2 | Control Faceplate | ⏳ next |
| 3 | Digital Speedometer + View 2 (speedo-only) | planned |
| 4 | Analog Tachometer (Canvas) | planned |
| 5 | View 1 composition (classic view) | planned |
| 6 | Telltales & Warnings | planned |
| 7 | Info screens (trip, trip metrics, fuel) | planned |
| 8 | Polish, docs, CAN bus integration notes | planned |

Folders `src/simulation/`, `qml/views/`, `qml/components/`, and
`qml/faceplate/` are reserved for later stages and currently empty.
# motorbike_instrumentcluster
