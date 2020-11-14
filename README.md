# Arc
Arc is an astrodynamics toolkit aimed at providing high-accuracy numerical propagation and orbit/trajectory analysis on spacecraft. It started as a personal project to learn more about the mathematics used in orbit determination/propagation. I've attempted to keep three development goals in mind:
 - Simple, unobscured code with sane variable names and logic
 - Adherence to as many international scientific standards as practical
 - No dependencies outside the Standard Template Library

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
	 - [x] Ephemeris Interpolation
	 - [x] Fixed-step Runge-Kutta integration
	 - [ ] Dormand-Prince integration
	 - [ ] Adams-Bashforth-Moulton integration
 - [ ] Perturbing force models
	 - [ ] Aspherical Earth gravity model (EGM-2008)
	 - [ ] Atmospheric Drag (Harris-Preister)
	 - [x] Third body gravity
	 - [ ] Solar Radiation Pressure
	 - [ ] Spacecraft Maneuvers
	 - [ ] Tidal variations
	 - [ ] Relativity
 - [ ] Data output
	 - [ ] Spacecraft Ephemerides/Covariance
		 - [x] STK format
		 - [ ] CCSDS OEM format
	 - [ ] Two-line element set (TLE)

