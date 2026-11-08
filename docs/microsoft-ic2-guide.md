# Microsoft IC2 interview guide

These are evidence-backed discussion prompts, not claims that every project is production-ready. Use the project source and README as the source of truth.

## Thirty-second explanations

- **Concurrent File Copy:** “This C++ project uses several reader threads and a writer thread around a bounded queue. Mutexes protect queue state, condition variables prevent busy waiting, and completion signalling lets the writer terminate cleanly. The key discussion is correctness under scheduling, not just raw throughput.”
- **Memory Allocation Simulator:** “This allocator models fixed-size memory management with linked lists and `sbrk`. I can compare first-fit and best-fit, then explain how splitting, freeing and coalescing maintain allocator state while exposing fragmentation tradeoffs.”
- **Minecraft Maze Runner:** “This collaborative C++ application generates mazes with recursive backtracking, integrates them into a Spigot world and provides route-solving modes. My documented work includes the Enhancement 2 shortest route, debugging route visualisation, tests and a menu implementation.”
- **Soil Organics:** “This team project connects a React frontend to Express routes, Sequelize models and MySQL, with product, review, authentication and administration flows. The strongest interview angle is tracing a feature across boundaries and identifying where integration tests and secret management matter.”
- **Colonoscopy Referral Triage:** “This academic capstone compares machine-learning approaches for referral-priority categories. It focuses on validation, leakage prevention and metrics such as macro F1 and urgent-category recall, while keeping clinician review and external validation as explicit safety requirements.”

| Project | Resume-ready description | Two interview talking points | Challenge | Design tradeoff |
|---|---|---|---|---|
| Concurrent File Copy | Built a POSIX-threaded file copier with a bounded producer-consumer queue. | Explain mutex/condition-variable coordination; discuss completion signalling and shared file-stream access. | Coordinating readers and a writer without busy waiting. | Simplicity of one shared queue versus throughput and deterministic line ordering. |
| Memory Allocation Simulator | Implemented first-fit and best-fit allocation with linked-list free-block tracking and `sbrk` expansion. | Compare fragmentation behavior; explain deallocation and coalescing invariants. | Maintaining consistent free and allocated lists after split/free operations. | Educational control with `sbrk` versus safety and portability of modern allocators. |
| Minecraft Maze Runner | Contributed recursive maze generation, BFS shortest-route integration, debugging and tests to a collaborative Spigot application. | Explain BFS predecessor reconstruction; discuss debugging a route rendered in a live world. | Aligning algorithmic state with Minecraft block state and existing menu flows. | Wall following is simpler; BFS gives shortest paths but requires more state. |
| Soil Organics | Contributed to a collaborative React/Express/MySQL grocery platform with reviews and administration. | Trace a request from React helper to Express controller and Sequelize model; discuss test gaps. | Coordinating frontend, backend and database behavior across a team. | Fast feature delivery versus stronger validation, authentication boundaries and integration coverage. |
| Colonoscopy Referral Triage | Developed a university capstone evaluating ML models for referral-priority prediction with safety-aware review workflows. | Explain multiclass and macro metrics; discuss leakage prevention and why clinical review remains necessary. | Optimising urgent-case recall without presenting predictions as clinical decisions. | Predictive performance versus interpretability, calibration and external validation. |

## Interview question prompts

| Area | Questions to practise |
|---|---|
| Threads | What predicate does each condition variable protect? How could a missed notification or an incorrect lock scope cause a hang? |
| Memory | When does first-fit differ from best-fit? What invariants must hold after splitting, freeing and coalescing? |
| Graphs | Why does BFS produce a shortest unweighted route? What does the predecessor structure store, and what are the complexity bounds? |
| Web and SQL | How does a React request reach a Sequelize model? Where would authentication, validation and transaction boundaries belong? |
| ML safety | Why use macro metrics? How would you detect leakage, calibrate confidence and prevent a prototype from being treated as a clinical decision? |
| Testing | Which checks were executed, which were blocked by dependencies, and what deterministic tests would you add next? |
