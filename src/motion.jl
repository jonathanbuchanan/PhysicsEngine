# Coulomb's Law

## Velocity
# Δx = v.x * Δt
# Δy = v.y * Δt
# Δz = v.z * Δt
function applyVelocity(particle, deltaTime)
  particle.position = particle.position + vec3(
    particle.velocity.x * deltaTime,
    particle.velocity.y * deltaTime,
    particle.velocity.z * deltaTime
  )
end

## Acceleration
# Δv.x = a.x * Δt
# Δv.y = a.y * Δt
# Δv.z = a.z * Δt
function applyAcceleration(particle, acceleration, deltaTime)
  particle.velocity = particle.velocity + vec3(
    acceleration.x * deltaTime,
    acceleration.y * deltaTime,
    acceleration.z * deltaTime
  )
end

## F = ma
## a = F/m
function applyForce(particle, force, deltaTime)
  mass = particleMass(particle)
  acceleration = vec3(
    force.x / mass,
    force.y / mass,
    force.z / mass
  )
  return acceleration
end
