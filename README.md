# Arc

[![GitHub version](https://badge.fury.io/gh/Naereen%2FStrapDown.js.svg)](https://github.com/mattstvan/arc)
![CMake](https://github.com/mattstvan/arc/workflows/CMake/badge.svg?branch=master&event=push)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/mattstvan/arc/graphs/commit-activity)
[![GitHub issues](https://img.shields.io/github/issues/Naereen/StrapDown.js.svg)](https://github.com/mattstvan/arc/issues/)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Naereen/StrapDown.js.svg)](https://github.com/mattstvan/arc/pull/)


Arc is an astrodynamics toolkit aimed at providing high-accuracy numerical propagation and orbit/trajectory analysis on spacecraft. It started as a personal project to learn more about the mathematics used in orbit determination/propagation. I've attempted to keep three development goals in mind:
 - Simple, unobscured code with sane variable names and logic
 - Adherence to as many international scientific standards as practical
 - No external dependencies outside the Standard Template Library

## Planned Features

 - [ ] Coordinate systems
	 - [x] International Celestial Reference Frame (ICRF)
	 - [x] International Terrestrial Reference Frame (ITRF/ECEF)
	 - [ ] True Equator Mean Equinox (TEME)
	 - [x] Keplerian elements
 - [ ] Planetary positions
	 - [ ] Numerical approximation
	 - [x] Ephemeris interpolation
	 - [ ] JPL ephemerides (DE430, etc)
 - [ ] Planetary orientations
 	 - [x] Earth (IAU 1980)
	 - [ ] Earth (IAU 2000/2006)
 - [x] Time handling
	 - [x] Coordinated Universal Time (UTC)
	 - [x] Universal Time (UT1)
	 - [x] Terrestrial Time (TT)
	 - [x] International Atomic Time (TAI)
	 - [x] Barycentric Dynamical Time (TDB)
	 - [x] Leap second
 - [ ] Orbital state propagation
	 - [x] Keplerian Approximation
	 - [ ] Ephemeris Interpolation
	 	- [x] Keplerian
	 	- [ ] Lagrange
	 	- [ ] Hermite
	 - [ ] Numerical integration
		 - [x] 4th-order Runge-Kutta
		 - [ ] Dormand-Prince
		 - [ ] Adams-Bashforth-Moulton
 - [ ] Perturbing force models
	 - [ ] Aspherical gravity models
	 	- [x] J2
	 	- [ ] J3
	 	- [ ] EGM-2008
	 	- [ ] GMM-3
	 - [ ] Atmospheric Drag
	 	- [x] U.S. Standard 1976
		- [ ] Harris-Priester
		- [ ] NASA Earth-GRAM
		- [ ] NASA Mars-GRAM
	 - [x] Third body gravity
	 - [ ] Solar Radiation Pressure
	 - [ ] Spacecraft Maneuvers
	 - [ ] Tidal variations
	 - [ ] Relativity
 - [ ] Data input
	 - [x] JSON parsing
	 - [ ] Python library
	 - [ ] External library call
 - [ ] Data output
	 - [ ] Spacecraft Ephemerides
		 - [x] STK format
		 - [ ] CCSDS OEM format
	 - [ ] Spacecraft Covariance
		 - [ ] STK format
		 - [ ] CCSDS OEM format	 	
	 - [ ] Two-line element set (TLE)

