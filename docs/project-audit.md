# Project audit

## Inventory

This monorepo contains curated snapshots of 29 projects: 27 repositories discovered through the GitHub account and recorded contribution search, plus the uploaded Maze Runner source snapshot and Colonoscopy Referral Triage capstone.

The original repository names and their descriptive portfolio directory names are recorded in [project-names.md](project-names.md).

Four source repositories were empty at mirroring time and retain placeholder READMEs. Projects with limited documentation are linked from the main README without invented descriptions.

The Maze Runner source was added from the uploaded ZIP archive. The archive contains 58 source, documentation and test files but no Git metadata, so its original commit history is not preserved in this monorepo.

The capstone entry links to `https://github.com/rmit-computing-technologies/Programming-Project-1.git`. GitHub returned 404 through this session. An uploaded archive subsequently supplied the capstone README and notebooks; the notebooks were added with outputs cleared. The archive's patient-level CSV and sample patient JSON were excluded because they contain healthcare and operational data.

## Verified findings

- Strongest recruiter-facing evidence: `concurrent-file-copy`, `memory-allocation-simulator`, `dictionary-algorithms-analysis`, `soil-organics-platform`, `cnn-machine-learning-assignment`, `minecraft-maze-runner` and `colonoscopy-referral-triage`.
- Existing build systems include Makefiles and npm manifests; project-specific instructions are retained in each directory.
- A missing `<cstdint>` include prevented the Memory Allocation Simulator from compiling with `-Werror`; the include was added as a minimal build fix.
- Generated dependencies, frontend build output, notebook checkpoints, macOS metadata and compiled object files were removed from this snapshot.
- Coursework submission documents and PDFs were excluded from the portfolio snapshot to reduce redistribution and privacy risk.
- Tests are documented only where test files or existing instructions provide evidence. Projects should not be described as passing tests unless a current run has been recorded.

## Incomplete documentation and test gaps

- The Soil Organics backend declares no real test command; the frontend has two visible test files and they pass with the committed lockfile after dependency installation, but no database integration test was run.
- Maze Runner has substantial fixtures but requires the external `mcpp` library and Minecraft server.
- The machine-learning capstone contains notebooks rather than a packaged application and has no reproducible dependency lockfile.
- Several small coursework repositories have limited README content and are not featured.

## Link and presentation audit

- All relative Markdown links to `projects/` paths passed local existence validation after the descriptive rename.
- No duplicate featured-project entry remains in the root README.
- External GitHub and portfolio URLs were not availability-tested from this environment.
- Generated dependencies, build output, checkpoints and compiled artifacts are excluded by the root `.gitignore` and were removed from the snapshot.

## Security and privacy findings

- The original Soil Organics snapshot contained hard-coded database credentials in both backend configuration files. Runtime source now reads required environment variables and no credential value is printed here. Treat any historically exposed credential as compromised and rotate it.
- The capstone's patient-level CSV and sample patient JSON were excluded. The notebooks' saved outputs were cleared.
- Student numbers, team names and third-party assets remain in some source documentation; review whether each is appropriate for public redistribution.
- No real `.env`, private key or PEM file is currently present in the portfolio snapshot; placeholder `.env.example` files are intentional.

## Recommendations

1. Rotate the historically exposed Soil Organics database credential before any further distribution.
2. Add a real backend test suite and environment-based configuration to Soil Organics.
3. Add a dependency/environment specification for the ML capstone using de-identified data.
4. Add deterministic file-content tests for Concurrent File Copy.
5. Add allocator invariant tests for split, free, coalescing, invalid free and exhaustion cases.
6. Preserve original histories through links or subtree imports only after licensing and team-sharing review.

## Validation status

**Passed:** Markdown/project-path validation, diff whitespace validation, sensitive-file filename checks, capstone notebook JSON/privacy validation, updated backend configuration syntax checks, Concurrent File Copy build and multi-file content smoke test, Memory Allocation Simulator compilation with `make all`, and Soil Organics frontend tests (`CI=true npm test -- --watchAll=false`, 2 suites/4 tests).

**Failed or blocked:** Maze Runner requires unavailable `mcpp` and Minecraft; the Memory Allocation Simulator generator requires the missing `bc` utility. Soil frontend tests pass but emit existing React DOM warnings and Jest reports open handles after completion.

**Not performed:** Soil Organics database integration tests, Minecraft integration tests, model retraining, and external-link availability checks. `npm ci` reported 81 dependency audit findings in the legacy Create React App dependency tree; no broad upgrade was applied.

## Maze Runner provenance

The Minecraft Maze Runner repository was supplied as:

`https://github.com/rmit-computing-technologies/cosc2804-sep-23-assignment-3-team-58-cosc2804-sep23`

GitHub remains inaccessible from this session, but the uploaded archive contains the source README, implementation, Makefile and tests. The portfolio preserves the source README as `projects/minecraft-maze-runner/SOURCE_README.md` and adds a recruiter-oriented README alongside it.
