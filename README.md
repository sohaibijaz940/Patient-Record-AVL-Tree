# CareIndex — from a patient-ID AVL tree to clinic workflows

**[Try the live CareIndex demo](https://sohaibijaz.dev/demos/careindex/tour/)** · [Case study](https://sohaibijaz.dev/projects/patient-record-avl-tree/) · [Portfolio](https://sohaibijaz.dev)

![Modern CareIndex interface](https://raw.githubusercontent.com/sohaibijaz940/sohaib-engineering-portfolio/main/public/previews/careindex.webp)

This repository preserves the original C++ Data Structures and Algorithms project for patient identifiers. The portfolio refinement is **CareIndex**, a synthetic clinic demonstration with an accompanying algorithm lab.

## Original foundation

Open `DSA project.sln` in Visual Studio to inspect/build the original coursework. Its solution and source folder are retained unchanged. The modern edition is maintained in the shared Next.js portfolio repository linked below.

## Modern demonstration

- Synthetic patient/clinician/admin workflows with sessions, role checks and ownership boundaries.
- Booking availability checked inside `BEGIN IMMEDIATE`, a partial unique index guarding scheduled slots, and booking/invoice writes in one transaction.
- Simulated billing and a guided recruiter tour; no genuine patient records or payment processing.
- An interactive AVL lab showing insert/search/delete, traversals and all four rotation cases.
- A detailed illustrated story and a captioned English explainer about the competing-request problem.

The teaching AVL tree is not the SQLite database's internal index. This is a student demonstration, not a production medical system. Production-readiness checks and limits are documented in the modern source.

## Source and setup

- [Complete modern source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio)
- [This project's modern page source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio/tree/main/src/app/demos/careindex/)
- [Local setup, providers and verification](https://github.com/sohaibijaz940/sohaib-engineering-portfolio#run-locally)
- [Engineering article source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio/blob/main/src/content/writing/careindex.mdx)
- [Original README, preserved for historical context](docs/ORIGINAL_README.md)

The portfolio is currently a local demonstration; a public hosted demo URL will be added after deployment. Links above open source code, not a hosted application. No localhost URL is presented as a public demo.
