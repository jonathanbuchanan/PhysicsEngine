# Main simulation loop
function simulate()
  # Create the simulation
  simulation = newSimulation()

  # Create the rendering setup
  windowWidth = 640
  windowHeight = 480
  windowTitle = "Simulation"

  Renderer.init()
  window = Renderer.createWindow(windowWidth, windowHeight, windowTitle)
  renderer = Renderer.createRenderer(window)

  function a_cback(key)
    println("'A' key pressed")
  end

  function b_cback(key)
    println("'B' key pressed")
  end

  Renderer.addKeyCallback(renderer, a_cback, Renderer.KeyA, Renderer.Press)
  Renderer.addKeyCallback(renderer, b_cback, Renderer.KeyB, Renderer.Press)

  while Renderer.windowCloseStatus(window) != true
    Renderer.render(renderer)
  end
  Renderer.terminate(renderer)
end

# Simulation object
"An object that encapsulates the state of a simulation"
mutable struct Simulation
  time::Float64
  objects::Array{Particle, 1}
end

"Creates a blank simulation"
function newSimulation()
  return Simulation(0, [])
end

"Runs a single step of a simulation"
function simulationStep!(simulation)
  simulation.time += 1
end

"Adds a particle to a simulation"
function addParticle!(simulation::Simulation, particle::Particle)
  push!(simulation.objects, particle)
end

"Removes a particle from a simulation"
function removeParticle!(simulation::Simulation, particle::Particle)
  filter!(a -> a != particle, simulation.objects)
end
