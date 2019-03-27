using Printf

function setupSimulation(simulation)
  electron = Electron(Vector3(0.0, 3.0, 2.0), Vector3(0.008, 0.0, -0.003))
  proton = Proton(Vector3(0.0, 0.0, 2.0), Vector3(-0.0008, 0.0, 0.0003))
  #neutron = Neutron(Vector3(0.0, 0.0, 5.0), Vector3(0.0, 0.0, 0.0))

  addParticle!(simulation, electron)
  addParticle!(simulation, proton)
  #addParticle!(simulation, neutron)
end

bottomMenu = nothing
entityLabel = nothing
timeLabel = nothing
pauseButton = nothing

inspectorMenu = nothing
inspectorLabel = nothing
kineticEnergyLabel = nothing

function setupMenus()
  menus = []

  global bottomMenu = createMenu()

  setMenuOrientation(bottomMenu, Horizontal)
  setMenuPosition(bottomMenu, Vector2(0.0, 0.0))
  setMenuSize(bottomMenu, Vector2(1280.0, 20.0))
  setMenuColor(bottomMenu, Vector4(0.3, 0.3, 0.3, 1.0))

  global entityLabel = createLabel()
  setLabelZ(entityLabel, 1)
  setLabelSize(entityLabel, Vector2(100.0, 15.0))
  setLabelPosition(entityLabel, Vector2(0.0, 2.5))
  setLabelColor(entityLabel, Vector4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(entityLabel, 15)
  setLabelText(entityLabel, "Entities: N")

  addControlToMenu(bottomMenu, entityLabel)

  global timeLabel = createLabel()
  setLabelZ(timeLabel, 1)
  setLabelSize(timeLabel, Vector2(100.0, 15.0))
  setLabelPosition(timeLabel, Vector2(100.0, 2.5))
  setLabelColor(timeLabel, Vector4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(timeLabel, 15)
  setLabelText(timeLabel, "Time: 0")

  addControlToMenu(bottomMenu, timeLabel)

  push!(menus, bottomMenu)

  #global pauseButton = createButton()

  #addControlToMenu(bottomMenu, pauseButton)



  global inspectorMenu = createMenu()

  setMenuOrientation(inspectorMenu, Vertical)
  setMenuPosition(inspectorMenu, Vector2(20.0, 200.0))
  setMenuSize(inspectorMenu, Vector2(200.0, 400.0))
  setMenuColor(inspectorMenu, Vector4(0.3, 0.3, 0.3, 1.0))

  push!(menus, inspectorMenu)

  global inspectorLabel = createLabel()
  setLabelZ(inspectorLabel, 1)
  setLabelSize(inspectorLabel, Vector2(180.0, 15.0))
  setLabelPosition(inspectorLabel, Vector2(10.0, 380.0))
  setLabelColor(inspectorLabel, Vector4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(inspectorLabel, 15)
  setLabelText(inspectorLabel, "Inspector")

  addControlToMenu(inspectorMenu, inspectorLabel)

  global positionLabel = createLabel()
  setLabelZ(positionLabel, 1)
  setLabelSize(positionLabel, Vector2(180.0, 15.0))
  setLabelPosition(positionLabel, Vector2(10.0, 360.0))
  setLabelColor(positionLabel, Vector4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(positionLabel, 15)
  setLabelText(positionLabel, "Position: ( , , )")

  addControlToMenu(inspectorMenu, positionLabel)

  global kineticEnergyLabel = createLabel()
  setLabelZ(kineticEnergyLabel, 1)
  setLabelSize(kineticEnergyLabel, Vector2(180.0, 15.0))
  setLabelPosition(kineticEnergyLabel, Vector2(10.0, 340.0))
  setLabelColor(kineticEnergyLabel, Vector4(1.0, 1.0, 1.0, 1.0))
  setLabelTextHeight(kineticEnergyLabel, 15)
  setLabelText(kineticEnergyLabel, "Kinetic Energy: ")

  addControlToMenu(inspectorMenu, kineticEnergyLabel)

  return menus
end

function resize(renderer, width, height)
  setMenuSize(bottomMenu, Vector2(convert(Float64, width), 20.0))
end

# Main simulation loop
function simulate()
  # Create the simulation
  simulation = newSimulation()

  # Create the rendering setup
  windowWidth = 1280
  windowHeight = 720
  windowTitle = "Simulation"

  Renderer.init()
  window = Renderer.createWindow(windowWidth, windowHeight, windowTitle)
  renderer = Renderer.createRenderer(window)
  Renderer.setResizeCallback(renderer, resize)
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

    inspectorReadout(simulation.objects[1])

    Renderer.render(renderer, simulation, menus)
  end

  Renderer.terminate(renderer)
end

function inspectorReadout(particle)
  setLabelText(positionLabel, Printf.@sprintf("Position: (%0.2f, %0.2f, %0.2f)", particle.position.x, particle.position.y, particle.position.z))
  setLabelText(kineticEnergyLabel, Printf.@sprintf("Kinetic Energy: %0.2f", kineticEnergy(particle) * 1000))
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
    forces[i] = Vector3(0.0, 0.0, 0.0)
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
