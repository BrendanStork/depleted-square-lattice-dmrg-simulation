# 1/5-Depleted Square Lattice Hubbard Model

## Overview

This project is a computational condensed matter physics research project focused on studying the Hubbard model on the 1/5-depleted square lattice using the open-source :contentReference[oaicite:0]{index=0} tensor network library.

The repository implements lattice geometry generation, Hubbard Hamiltonian construction, and DMRG simulation workflows for investigating strongly correlated electron systems and geometry-dependent quantum behavior in depleted lattice structures.

The project combines:

* Computational many-body physics
* Tensor network simulations using ITensor
* Lattice graph construction
* Hubbard Hamiltonian generation
* Numerical modeling of correlated quantum systems
* Scientific computing workflows

---

## Physics Background

The Hubbard model is one of the central models in condensed matter physics for studying interacting fermionic systems. It captures the competition between:

* Electron hopping between neighboring lattice sites
* On-site Coulomb repulsion

The Hamiltonian is given by:

```text
H = -t Σ(c†ᵢσ cⱼσ + h.c.) + U Σnᵢ↑ nᵢ↓
```

where:

* `t` is the hopping parameter
* `U` is the on-site interaction strength
* `c†(i,σ)` and `c(i,σ)` are fermionic creation and annihilation operators
* `n(i,σ)` is the number operator

This project focuses specifically on the **1/5-depleted square lattice geometry**, whose modified connectivity can produce nontrivial magnetic and correlated quantum behavior.

---

## Project Goals

The primary goals of this project are:

* Construct 1/5-depleted square lattice geometries
* Build lattice-aware Hubbard Hamiltonians
* Perform DMRG simulations using ITensor
* Investigate geometry-dependent correlated behavior
* Explore magnetic and many-body quantum phases
* Develop reusable simulation and analysis workflows

---

## Features

### Current Features

* [x] 1/5-depleted square lattice generation
* [x] Configurable Hubbard Hamiltonian construction
* [x] Custom hopping parameter definitions
* [x] ITensor-based DMRG simulation workflows
* [x] Ground state calculation setup
* [x] Scientific analysis and experimentation tools

### Planned Features

* [ ] Correlation function measurements
* [ ] Entanglement entropy analysis
* [ ] Phase diagram exploration
* [ ] Visualization tools
* [ ] HPC scaling workflows
* [ ] Additional lattice geometries
* [ ] Extended Hubbard-type models

---

## Repository Structure

```text
.
├── src/                # Core simulation code
├── lattices/           # Lattice geometry definitions
├── hamiltonians/       # Hamiltonian construction
├── simulations/        # DMRG simulation workflows
├── observables/        # Measurement and analysis tools
├── notebooks/          # Exploratory notebooks
├── tests/              # Validation and testing
├── figures/            # Generated plots and visualizations
├── data/               # Simulation outputs
├── README.md
└── requirements.txt
```

---

## Technical Focus

This project emphasizes:

* Computational modeling of strongly correlated systems
* Lattice-dependent Hamiltonian construction
* Tensor network simulations using ITensor
* Numerical experimentation in condensed matter physics
* Modular scientific computing workflows
* Clean and reproducible simulation organization

---

## Methods and Algorithms

This project uses:

* Density Matrix Renormalization Group (DMRG)
* Matrix Product States (MPS)
* Tensor network methods via ITensor
* Hubbard model Hamiltonians
* Numerical many-body simulation techniques
* Fermionic lattice models

---

## Scientific Motivation

Depleted lattice systems provide an important platform for studying:

* Strong electronic correlations
* Competing quantum phases
* Emergent magnetic behavior
* Geometry-driven localization effects
* Quantum criticality
* Low-dimensional many-body physics

The 1/5-depleted square lattice is particularly interesting because its modified connectivity can generate behavior not present in conventional square lattice systems.

---

## Technologies

This project uses:

* Python
* NumPy
* SciPy
* :contentReference[oaicite:1]{index=1}
* Jupyter notebooks
* Git/GitHub

---

## Future Directions

Long-term goals include extending the framework toward:

* Additional lattice geometries
* Spin models
* Time evolution methods
* Finite-temperature simulations
* Automated parameter sweeps
* HPC-oriented simulation workflows
* Expanded observable and analysis support

---

## Author

Brendan Stork

Physics graduate student with experience in:

* Computational physics
* Quantum many-body systems
* Tensor network methods
* Scientific programming
* Quantum computing
* Machine learning

---

## License

This project is released under the MIT License.

---

## Acknowledgments

This project utilizes the open-source :contentReference[oaicite:2]{index=2} tensor network library for DMRG and tensor network simulations.
