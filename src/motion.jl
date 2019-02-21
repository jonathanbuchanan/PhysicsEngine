# Coulomb's Law
# F = k * ((q1 * q2) / r²)
function coulombs(particle1, particle2)
  k = 0.0003
  force = k * ((charge(particle1) * charge(particle2)) / max(magnitude(particle1.position - particle2.position), 0.0001))
  q = (charge(particle1) * charge(particle2))
  ma = max(magnitude(particle1.position - particle2.position), 0.0001)
  positive = vec3(
    force * (particle1.position.x - particle2.position.x),
    force * (particle1.position.y - particle2.position.y),
    force * (particle1.position.z - particle2.position.z)
  )
  negative = vec3(
    -force * (particle1.position.x - particle2.position.x),
    -force * (particle1.position.y - particle2.position.y),
    -force * (particle1.position.z - particle2.position.z)
  )
  return (positive, negative)
end

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
