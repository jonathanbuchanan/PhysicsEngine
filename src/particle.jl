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

# Radius
function particleRadius(::Electron)
  return 0.04
end

function particleRadius(::Proton)
  return 0.3
end

function particleRadius(::Neutron)
  return 0.3
end

# Kinetic Energy
function kineticEnergy(particle)
  return 0.5 * particleMass(particle) * magnitude(particle.velocity) * magnitude(particle.velocity)
end
