using PhysicsEngine
using Test

projectName = "PhysicsEngine"
testFiles = [
  "simulation_test.jl"
]

for file in testFiles
  include(file)
end
