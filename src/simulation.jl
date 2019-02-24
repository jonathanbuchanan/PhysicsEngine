function setupSimulation(simulation)
  electron = Electron(vec3(0.0, 3.0, 2.0), vec3(0.008, 0.0, -0.003))
  proton = Proton(vec3(0.0, 0.0, 2.0), vec3(-0.0008, 0.0, 0.0003))
  #neutron = Neutron(vec3(0.0, 0.0, 5.0), vec3(0.0, 0.0, 0.0))

  addParticle!(simulation, electron)
  addParticle!(simulation, proton)
  #addParticle!(simulation, neutron)
end

entityLabel = nothing
timeLabel = nothing

function setupMenus()
  menus = []

  bottomMenu = createMenu()

  setMenuOrientation(bottomMenu, Horizontal)
  setMenuPosition(bottomMenu, vec2(0.0, 0.0))
  setMenuSize(bottomMenu, vec2(640.0, 20.0))
  setMenuColor(bottomMenu, vec4(0.3, 0.3, 0.3, 1.0))

  global entityLabel = createLabel()
  setLabelZ(entityLabel, 1)
  setLabelSize(entityLabel, vec2(100.0, 15.0))
  setLabelPosition(entityLabel, vec2(0.0, 2.5))
  setLabelColor(entityLabel, vec4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(entityLabel, 15)
  setLabelText(entityLabel, "Entities: N")

  addControlToMenu(bottomMenu, entityLabel)

  global timeLabel = createLabel()
  setLabelZ(timeLabel, 1)
  setLabelSize(timeLabel, vec2(100.0, 15.0))
  setLabelPosition(timeLabel, vec2(100.0, 2.5))
  setLabelColor(timeLabel, vec4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(timeLabel, 15)
  setLabelText(timeLabel, "Time: 0")

  addControlToMenu(bottomMenu, timeLabel)

  push!(menus, bottomMenu)

  return menus
end

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

  function esc_callback(renderer, key)
    Renderer.closeWindow(window)
  end

  Renderer.addKeyCallback(renderer, esc_callback, Renderer.Escape, Renderer.Press)

  menus = setupMenus()

  setupSimulation(simulation)

  step = 0
  while Renderer.windowCloseStatus(window) != true
    stepsperframe = 10
    for i = 1:stepsperframe
      simulationStep!(simulation)
    end

    entityCount = length(simulation.objects)
    setLabelText(entityLabel, "Entities: $entityCount")
    time = simulation.time
    setLabelText(timeLabel, "Time: $time")

    Renderer.render(renderer, simulation, menus)
  end

  Renderer.terminate(renderer)
end

# Contains a particle and the necessary rendering handle
mutable struct ParticleContainer
  particle::Particle
  renderObject::Ptr{Cvoid}
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
  forces = Array{Vector3}(undef, length(simulation.objects))
  for i in 1:length(simulation.objects)
    forces[i] = vec3(0.0, 0.0, 0.0)
  end
  for i in 1:length(simulation.objects)
    for j in (i + 1):length(simulation.objects)
      (f1, f2) = coulombs(simulation.objects[i], simulation.objects[j])
      forces[i] = forces[i] + f1
      forces[j] = forces[j] + f2
    end
  end
  for i in 1:length(simulation.objects)
    particle = simulation.objects[i]
    acceleration = applyForce(particle, forces[i], 1)
    applyAcceleration(particle, acceleration, 1)
    applyVelocity(particle, 1)
  end
end

"Adds a particle to a simulation"
function addParticle!(simulation::Simulation, particle::Particle)
  push!(simulation.objects, particle)
end

"Removes a particle from a simulation"
function removeParticle!(simulation::Simulation, particle::Particle)
  filter!(a -> a != particle, simulation.objects)
end
