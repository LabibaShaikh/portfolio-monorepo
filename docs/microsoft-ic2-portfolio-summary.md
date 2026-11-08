# Microsoft Software Engineer IC2 Portfolio Summary

This portfolio presents Shaikh Naima Labiba, a Bachelor of Computer Science graduate from RMIT University, through evidence from academic, personal and collaborative software projects. The strongest examples are ordered by the engineering fundamentals they make easiest to discuss in an interview.

## Five strongest projects

| Project | Microsoft-relevant competencies | Resume-ready bullet | Verified evidence |
|---|---|---|---|
| [Concurrent File Copy](../projects/concurrent-file-copy) | C++, concurrency, synchronization, debugging and collaboration | Built a POSIX-threaded file copier using a bounded producer-consumer queue, mutexes and condition variables; collaborated on shared file-processing behavior and tested multi-file output. | Compiles with the repository Makefile; local smoke test copied and compared 10 files. |
| [Memory Allocation Simulator](../projects/memory-allocation-simulator) | C++, memory management, linked lists, algorithms and invariants | Implemented first-fit and best-fit allocation over linked-list state with `sbrk` expansion, deallocation and adjacent free-block coalescing. | `make all` compiles both allocator variants after a minimal standards-header fix. |
| [Minecraft Maze Runner](../projects/minecraft-maze-runner) | C++, BFS/DFS reasoning, integration debugging and teamwork | Contributed recursive-backtracking maze generation and an Enhancement 2 BFS shortest-route implementation to a collaborative Spigot 1.19.4 application. | Source and fixtures are present; build is blocked here by unavailable `mcpp` and Minecraft dependencies. |
| [Soil Organics Platform](../projects/soil-organics-platform/README.portfolio.md) | React, Node.js, REST, SQL, authentication and maintainability | Contributed to a collaborative React/Express/Sequelize/MySQL grocery platform covering products, reviews, shopping flows and administration. | Frontend test files and package scripts are present; database integration requires local services and environment configuration. |
| [Colonoscopy Referral Triage](../projects/colonoscopy-referral-triage) | Python, model evaluation, data validation, safety and responsible engineering | Worked on an academic capstone comparing multiclass referral-priority models with leakage-aware validation and clinically cautious review workflows. | Notebooks are valid JSON with outputs cleared; patient-level files are excluded and no retraining result is claimed. |

## Interview topics

- **C++ and memory:** ownership, pointer arithmetic, allocator invariants, fragmentation, first-fit versus best-fit and why `sbrk` is educational rather than production-safe.
- **Concurrency:** bounded queues, producer-consumer coordination, condition-variable predicates, completion signalling, deadlock avoidance and nondeterministic ordering.
- **Algorithms:** recursive backtracking, BFS predecessor maps, shortest-path reconstruction, linked-list traversal and time/space complexity.
- **Web engineering:** request flow from React to Express and Sequelize, SQL persistence boundaries, authentication, environment-based configuration and integration-test gaps.
- **Machine learning:** multiclass metrics, macro averaging, leakage prevention, urgent-category recall, uncertainty flags and why a clinical prototype is not a medical product.
- **Engineering practice:** debugging external integrations, documenting limitations, preserving team attribution and distinguishing executed checks from blocked checks.

## Scope and evidence

These are academic and collaborative projects, not claims of professional production ownership. The portfolio README and each project README identify contribution boundaries. The [audit](project-audit.md) records commands that were actually run, blocked dependencies and known security or privacy limitations.
