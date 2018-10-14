using PhysicsEngine
using Test

cd("../")

projectName = "PhysicsEngine"
testFiles = [
  "simulation_test.jl"
  "grid_test.jl"
  "vector_test.jl"
  "particle_test.jl"
  "renderer_test.jl"
]

for file in testFiles
  include(file)
end
