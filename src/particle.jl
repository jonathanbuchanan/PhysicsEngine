abstract type Particle end

mutable struct Electron <: Particle
  position::Vector3
  velocity::Vector3
end

mutable struct Proton <: Particle
  position::Vector3
  velocity::Vector3
end

mutable struct Neutron <: Particle
  position::Vector3
  velocity::Vector3
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
function particleMass(::Electron)
  return 1
end

function particleMass(::Proton)
  return 10
end

function particleMass(::Neutron)
  return 10
end
