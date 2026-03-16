# Contributing Guidelines

## Purpose
This project uses a small layered CRUD system and targets native C++ (C++14) on Windows. These guidelines describe coding standards, dependency management, database integration steps, and WIN32 rendering instructions so contributions remain consistent and build reliably in Visual Studio 2022.

## Coding Style & Formatting
- Follow the project's `.editorconfig` rules for indentation, naming, and formatting. If `.editorconfig` is missing, add one matching existing source style (4 spaces, no tabs).
- Keep functions short and single-responsibility. Prefer clear names: `EmployeeRepository`, `IEmployeeRepository`, `Application::run`.
- Document non-obvious behavior with inline comments above functions. Use Doxygen-style comments for public APIs when helpful.

## Project Layout
- `src/` — application source files (e.g., `Employee.cpp`, `Header1.h`).
- `third_party/` — vendored third-party single-file libs (if necessary).
- `build/` — local build artifacts (ignore in git).

## Dependency Management
- Prefer `vcpkg` for native dependency management. Document required packages in `vcpkg.json` or README. Example packages: `sqlite3`, `sqlitecpp`, `nanodbc`, `msodbcsql`.
- For NuGet use only managed or mixed packages appropriate for native projects (e.g., `System.Data.SqlClient` is for .NET; avoid mixing CLR unless deliberate).
- In Visual Studio, enable automatic vcpkg integration or set `VCPKG_ROOT` and use `Project > C/C++ > General > Additional Include Directories` and `Linker > Input > Additional Dependencies` as needed.
- Bundle minimal runtime DLLs or document required runtime libraries in README.

## Database Integration: Recommended Steps
1. Choose a database for the feature: SQLite for embedded, SQL Server for enterprise, MySQL for LAMP ecosystems.
2. Add the appropriate native client library via vcpkg or direct download:
   - SQLite: `sqlite3` (amalgamation) or `SQLiteCpp` wrapper (`vcpkg install sqlite3 sqlitecpp`).
   - SQL Server: ODBC driver (`msodbcsql17`) and `nanodbc` for C++ wrapper (`vcpkg install nanodbc msodbcsql`).
   - MySQL: `mysql-connector-c++` (`vcpkg install mysql-connector-cpp`).
3. Configure project properties:
   - Include directories to header files.
   - Linker Additional Dependencies to required `.lib` files.
   - For dynamic libs, ensure DLLs are available on PATH or copied to output directory.
4. Implement a thin persistence layer that implements `IEmployeeRepository`:
   - Keep SQL/DB code isolated in `src/db/`.
   - Use parameterized queries to avoid SQL injection.
   - Return domain objects (`Employee`) and map DB columns carefully.
5. Implement migrations or simple CREATE TABLE statements on startup for SQLite.
6. Add error handling and logging; do not throw raw DB exceptions across module boundaries.

## WIN32 Rendering: Recommended Steps
1. Decide rendering technology:
   - Simple UI: GDI/GDI+ (easy, legacy).
   - Modern 2D: Direct2D (hardware accelerated). Link `d2d1.lib`.
   - GPU: Direct3D 11/12 for 3D or advanced 2D; add `d3d11.lib`, `dxgi.lib`.
2. Add a renderer module, e.g., `src/render/Win32Renderer.*`:
   - One responsibility: create window class, manage device resources, and render frames.
   - Keep UI and business logic separate; communicate via thread-safe message queues or events.
3. Linker settings: `User32.lib`, `Gdi32.lib`, `D2d1.lib`, `Dwrite.lib`, (`d3d11.lib`, `dxgi.lib`) as required.
4. Use double-buffering/backbuffers and handle WM_PAINT, WM_SIZE properly.
5. Make the application DPI-aware (manifest or API call) for correct scaling.

## Compatibility & Build
- Target both x86 and x64 configurations and test both.
- Ensure Windows SDK for chosen APIs is installed (Windows 10/11 SDK as appropriate).
- Document required Visual Studio components (Desktop development with C++ and vcpkg support).

## Testing & CI
- Add unit tests for repository logic (mock DB or use an in-memory SQLite DB for tests).
- In CI, install vcpkg and required packages, set up a test DB, and run tests on both x86/x64.

## Pull Requests
- Small focused PRs preferred.
- Include a short description of changes, build instructions if dependencies changed, and test steps.

## Contact
If you change dependency management (switch to vcpkg/NuGet), update this file and inform maintainers.