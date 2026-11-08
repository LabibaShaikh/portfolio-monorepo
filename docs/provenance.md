# Provenance, attribution and publishing notes

## Source of truth

Each project directory is a snapshot of an existing GitHub repository. The original repository should be used for complete Git history, branches, issues and pull requests. This monorepo does not claim to preserve every original commit in its current snapshot.

For future updates, history can be preserved by importing each repository with `git subtree add` from its original default branch. That should be done only after confirming the repository's sharing and licensing terms.

## Attribution

Team projects retain the team-member names and original links present in their source documentation. Contributions should be described as individual work only where the source README, contribution records or commit history supports that description.

## Licensing

The source repositories use mixed or unspecified licensing. This portfolio intentionally does not add a blanket licence to third-party or university coursework. Review each source repository's licence before redistributing code outside GitHub.

## Privacy and sensitive material

The snapshot excludes generated dependencies, build output, compiled objects, notebook checkpoints, submission PDFs/documents and environment files. Secrets must never be copied into this repository; use local `.env` files based on committed `.env.example` files.

Before publishing additional projects, check for API keys, database credentials, private datasets, patient-level data, personal contact details and university restrictions.

The Soil Organics snapshot previously contained hard-coded database credentials inherited from the original project. Runtime configuration now requires environment variables, and only placeholders are committed in `.env.example` files. Any credential previously used with the original host must still be rotated by its owner because it remains exposed in repository history; this change does not rewrite history. The capstone patient dataset was intentionally excluded.
