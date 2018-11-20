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
  camera = Renderer.getCamera(renderer)

  registerControls(renderer, camera)

  function esc_callback(key)
    Renderer.closeWindow(window)
  end

  Renderer.addKeyCallback(renderer, esc_callback, Renderer.Escape, Renderer.Press)

  step = 0
  while Renderer.windowCloseStatus(window) != true
    Renderer.render(renderer)
    Renderer.cameraSetUp(camera, vec3(10 * sin(step), 10 * cos(step), 0.0))
    step += 0.01
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
