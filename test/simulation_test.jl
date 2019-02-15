import PhysicsEngine

@testset "Simulation" begin
  sim = PhysicsEngine.newSimulation()

  # Time test
  initialTime = sim.time
  PhysicsEngine.simulationStep!(sim)
  finalTime = sim.time
  @test finalTime == initialTime + 1

  # Test add particle
  particle = PhysicsEngine.Electron([1, 1, 1], [2, 2, 2])
  @test (particle in sim.objects) == false
  PhysicsEngine.addParticle!(sim, particle)
  @test (particle in sim.objects) == true


  # Remove particle
  PhysicsEngine.removeParticle!(sim, particle)
  @test (particle in sim.objects) == false
end
