# Simulation object
"An object that encapsulates the state of a simulation"
mutable struct Simulation
  time::Float64
end

"Creates a blank simulation"
function newSimulation()
  return Simulation(0)
end

"Runs a single step of a simulation"
function simulationStep!(simulation)
  simulation.time += 1
end
