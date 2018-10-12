abstract type Particle end

mutable struct Electron <: Particle
  position::Vector
  velocity::Vector
end

mutable struct Proton <: Particle
  position::Vector
  velocity::Vector
end

mutable struct Neutron <: Particle
  position::Vector
  velocity::Vector
end

# Properties of particles

# Spin
function spin(::Electron)
  return 1 / 2
end

function spin(::Proton)
  return 1 / 2
end

function spin(::Neutron)
  return 1 / 2
end



# Charge
function charge(::Electron)
  return -1
end

function charge(::Proton)
  return 1
end

function charge(::Neutron)
  return 0
end



# Mass (kg)
function mass(::Electron)
  return 9.109e-31
end

function mass(::Proton)
  return 1.673e-27
end

function mass(::Neutron)
  return 1.675e-27
end
