import PhysicsEngine

@testset "Vector" begin
  v1 = PhysicsEngine.Vector3((1.0, 5.0, -2.0))
  v2 = PhysicsEngine.Vector3((5.5, -4.0, -0.5))

  @test v1 + v2 == PhysicsEngine.Vector3((6.5, 1.0, -2.5))
  @test v1 - v2 == PhysicsEngine.Vector3((-4.5, 9.0, -1.5))
  @test PhysicsEngine.dot(v1, v2) == 5.5 + -20.0 + 1.0
  @test v1 * v2 == PhysicsEngine.Vector3((-10.5, -10.5, -31.5))
end
