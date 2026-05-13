# 1/5-Depleted Square Lattice Hubbard Model Simulation

## Overview

This project is a computational condensed matter physics framework for studying the Hubbard model on the 1/5-depleted square lattice using tensor network and density matrix renormalization group (DMRG) techniques.

The repository is designed to investigate strongly correlated electron systems, emergent many-body phenomena, and geometry-dependent quantum behavior arising from depleted lattice structures.

The project combines:

* Computational many-body physics
* Tensor network methods
* Numerical linear algebra
* Lattice graph construction
* Hamiltonian generation
* Quantum simulation infrastructure
* Scientific computing workflows

---

## Physics Background

The Hubbard model is one of the central models in condensed matter physics for studying interacting fermionic systems. It captures the competition between:

* Electron hopping between neighboring lattice sites
* On-site Coulomb repulsion

The Hamiltonian is given by:

[
H = -t \sum_{\langle i,j \rangle,\sigma} \left(c^{\dagger}*{i\sigma} c*{j\sigma} + h.c.\right) + U \sum_i n_{i\uparrow} n_{i\downarrow}
]

where:

* ( t ) is the hopping parameter
* ( U ) is the on-site interaction strength
* ( c^{\dagger}*{i\sigma} ) and ( c*{i\sigma} ) are fermionic creation and annihilation operators
* ( n_{i\sigma} ) is the number operator

This project focuses specifically on the **1/5-depleted square lattice geometry**, which introduces nontrivial connectivity and frustration effects that can produce rich correlated phases.

---

## Project Goals

The primary goals of this project are:

* Construct flexible lattice-aware Hubbard Hamiltonians
* Implement scalable tensor network workflows
* Perform DMRG ground state calculations
* Investigate geometry-dependent correlated behavior
* Explore magnetic ordering and many-body phases
* Develop reusable scientific simulation infrastructure

---

## Features

### Current / Planned Features

* [x] Custom lattice graph generation
* [x] Hubbard Hamiltonian construction
* [x] Configurable hopping structure
* [x] Fermionic operator handling
* [x] Sparse operator workflows
* [ ] DMRG implementation
* [ ] Ground state calculations
* [ ] Correlation function measurements
* [ ] Entanglement entropy analysis
* [ ] Phase diagram exploration
* [ ] Time evolution methods
* [ ] Visualization tools
* [ ] HPC scaling support

---

## Repository Structure

```text
.
├── src/                # Core simulation code
├── lattices/           # Lattice geometry definitions
├── hamiltonians/       # Hamiltonian generation modules
├── dmrg/               # Tensor network and DMRG workflows
├── observables/        # Measurements and analysis tools
├── notebooks/          # Exploratory notebooks and testing
├── tests/              # Unit and validation tests
├── figures/            # Generated plots and visualizations
├── data/               # Simulation outputs
├── README.md
└── requirements.txt
```

---

## Technical Focus

This project emphasizes:

* Modular simulation architecture
* Separation of lattice and Hamiltonian logic
* Reusable physics abstractions
* Scalable numerical workflows
* Clean scientific software engineering practices

The codebase is intended to evolve into a general-purpose strongly correlated lattice simulation framework.

---

## Methods and Algorithms

The project uses or plans to use:

* Density Matrix Renormalization Group (DMRG)
* Matrix Product States (MPS)
* Tensor network methods
* Sparse linear algebra
* Exact diagonalization for benchmarking
* Trotterized time evolution
* Fermionic operator algebra

---

## Scientific Motivation

Depleted lattice systems provide an important platform for studying:

* Strong electronic correlations
* Competing quantum phases
* Emergent magnetic behavior
* Geometry-driven localization effects
* Quantum criticality
* Low-dimensional many-body physics

The 1/5-depleted square lattice is particularly interesting because the modified connectivity can generate behavior not present in ordinary square lattice systems.

---

## Technologies

This project uses:

* Python
* NumPy
* SciPy
* ITensor 
* Jupyter notebooks




## Example Future Usage

```python
from lattices import DepletedSquareLattice
from hamiltonians import HubbardHamiltonian

lattice = DepletedSquareLattice(Lx=8, Ly=8)

H = HubbardHamiltonian(
    lattice=lattice,
    t=1.0,
    U=4.0
)
```

---

## Research Direction

Long-term goals include extending the framework toward:

* More general lattice geometries
* Multi-orbital models
* Spin models
* Quantum dynamics
* Finite temperature methods
* Quantum computing interfaces
* Automated simulation pipelines

---

## Author

Brendan Stork

Physics graduate student with experience in:

* Quantum computing
* Computational physics
* Tensor network methods
* Machine learning
* Scientific programming
* Strongly correlated quantum systems

---

## License

This project is released under the MIT License.

---

## Acknowledgments

This project draws inspiration from research in:

* Strongly correlated electron systems
* Condensed matter theory
* Tensor network methods
* Computational quantum physics
* Hubbard model simulations

