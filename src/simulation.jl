function setupSimulation(simulation)
  electron = Electron(vec3(1.0, 5.0, 5.0), vec3(0.008, 0.0, 0.0))
  proton = Proton(vec3(-1.0, -5.0, 5.0), vec3(0.0, 0.0, 0.0))
  neutron = Neutron(vec3(0.0, 0.0, 5.0), vec3(0.0, 0.0, 0.0))

  addParticle!(simulation, electron)
  addParticle!(simulation, proton)
  addParticle!(simulation, neutron)
end

function setupMenus()
  menus = []

  bottomMenu = createMenu()

  setMenuOrientation(bottomMenu, Horizontal)
  setMenuPosition(bottomMenu, vec2(0.0, 0.0))
  setMenuSize(bottomMenu, vec2(640.0, 30.0))
  setMenuColor(bottomMenu, vec4(0.3, 0.3, 0.3, 1.0))

  entityLabel = createLabel()
  setLabelZ(entityLabel, 1)
  setLabelSize(entityLabel, vec2(100.0, 30.0))
  setLabelPosition(entityLabel, vec2(0.0, 0.0))
  setLabelColor(entityLabel, vec4(1.0, 1.0, 1.0, 1.0))
  setLabelText(entityLabel, "Label.")

  addControlToMenu(bottomMenu, entityLabel)


#button = createButton(vec2(100.0, 100.0), vec2(0.0, 0.0));
#Button *b = getButton(&button);
#b->highlight = vec4(1.0, 1.0, 1.0, 1.0);
#b->select = vec4(1.0, 0.0, 1.0, 1.0);
#b->action = test_callback;
#b->text = "Button";
#b->textColor = vec4(0.5, 0.5, 0.5, 1.0);
#b->z_index = 1;
#addControlToMenu(&renderer->menu, &button);

#label = createLabel(vec2(100.0, 100.0), vec2(0.0, 100.0));
#Label *l = getLabel(&label);
#l->color = vec4(1.0, 1.0, 1.0, 1.0);
#l->text = "I am a label.";
#l->z_index = 1;
#addControlToMenu(&renderer->menu, &label);

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
    Renderer.render(renderer, simulation, menus)
    #Renderer.cameraSetUp(camera, vec3(10 * sin(step), 10 * cos(step), 0.0))
    #step += 0.01

    stepsperframe = 10
    for i = 1:stepsperframe
      simulationStep!(simulation)
    end
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
