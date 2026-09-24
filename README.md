# Equipment Inspection Recorder

A C++23 command-line application for registering industrial equipment and
recording inspection measurements. It stores data in memory for the duration
of the program and reports an inspection result based on configured limits.

## Features

- Register equipment with an identifier, name, and category.
- Find registered equipment by identifier.
- Record temperature, vibration, and operating-hours measurements.
- Evaluate inspections as **Within Limits**, **Maintenance Needed**, or
  **Damaged**.
- View an equipment item's details and recorded inspections.
- Display a summary of all registered equipment.

The available categories are electric motors, hand tools, cutting tools, and
welding tools.

## Requirements

- A C++23-capable compiler (the Makefile defaults to `g++`).
- `make`.

The project uses only the C++ standard library.

## Build and run

From the project root, run `make app`. The Makefile places build artifacts in
`bin/` and `build/`, then starts the interactive application. To remove
generated artifacts, run `make clean`.

## Menu

The application offers options to add equipment, find equipment by identifier,
record an inspection, display an equipment item's inspection information,
display all equipment, or exit.

When an unknown equipment ID is entered, the application reports that it was
not found instead of accessing a nonexistent record.

## Project layout

- `app/` — application entry point.
- `src/` — domain models, in-memory database, UI, and menu handling.
- `tests/` — test scaffolding and test output.
- `Makefile` — build targets.

## License

This project is available under the [MIT License](LICENSE).
