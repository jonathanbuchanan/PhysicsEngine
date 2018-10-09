import PhysicsEngine

@testset "Simulation" begin
  sim = PhysicsEngine.newSimulation()
  initialTime = sim.time
  PhysicsEngine.simulationStep!(sim)
  finalTime = sim.time
  @test finalTime == initialTime + 1
end
