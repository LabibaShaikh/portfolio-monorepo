# Project audit

## Inventory

This monorepo contains snapshots of 28 projects: 27 repositories discovered through the GitHub account and recorded contribution search, plus the uploaded Maze Runner source snapshot and Colonoscopy Referral Triage capstone.

`A3_Assessment`, `Assign1-s12345-s67890`, `book-grocer`, `BSA`, `C-`, `Database_Systems_s3954789_A3`, `interview`, `LeetCode`, `MachineLearning_A2`, `methodologies`, `Methodology`, `my-pokemon-app`, `OSP_A1`, `OSP_A3`, `Patient0`, `Project1`, `Project1-C--`, `s3954789_ML_A2`, `sandworm-apollo`, `starter_code_111`, `TheMemoryLeakers_COSC1076_Assignment2`, `Trading_Bot`, `Vacuum_clean_apt`, `s3954789-s3946776-a2`, `s3954789-s3946776-a2-HD`, `AlgoAnalysisAssgnmt1_grp48` and `math_2`.

The four empty repositories have retained placeholder READMEs. Projects with limited documentation are linked from the main README without invented descriptions.

The Maze Runner source was added from the uploaded ZIP archive. The archive contains 58 source, documentation and test files but no Git metadata, so its original commit history is not preserved in this monorepo.

The capstone entry links to `https://github.com/rmit-computing-technologies/Programming-Project-1.git`. GitHub returned 404 through this session, so no source files, languages or individual contribution claims were copied from it.

An uploaded archive subsequently supplied the capstone README and notebooks. The notebooks were added with outputs cleared. The archive's patient-level CSV and sample patient JSON were excluded because they contain healthcare and operational data.

## Quality observations

- Strongest recruiter-facing evidence: `OSP_A1`, `OSP_A3`, `Assign1-s12345-s67890`, `s3954789-s3946776-a2`, `s3954789_ML_A2`, `sandworm-apollo` and `Trading_Bot`.
- Existing build systems include Makefiles and npm manifests; project-specific instructions are retained in each directory.
- Generated dependencies, frontend build output, notebook checkpoints, macOS metadata and compiled object files were removed from this snapshot.
- Coursework submission documents and PDFs were excluded from the portfolio snapshot to reduce redistribution and privacy risk.
- Tests are documented only where test files or existing instructions provide evidence. Projects should not be described as passing tests unless a current run has been recorded.

## Maze Runner provenance

The Minecraft Maze Runner repository was supplied as:

`https://github.com/rmit-computing-technologies/cosc2804-sep-23-assignment-3-team-58-cosc2804-sep23`

GitHub remains inaccessible from this session, but the uploaded archive contains the source README, implementation, Makefile and tests. The portfolio preserves the source README as `projects/minecraft-maze-runner/SOURCE_README.md` and adds a recruiter-oriented README alongside it.
