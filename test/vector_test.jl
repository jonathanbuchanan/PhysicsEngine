import PhysicsEngine

@testset "Vector2" begin
  v1 = PhysicsEngine.Vector2((5.0, 7.0))
  v2 = PhysicsEngine.Vector2((-3.5, 2.5))

  @test v1 + v2 == PhysicsEngine.Vector2((1.5, 9.5))
  @test v1 - v2 == PhysicsEngine.Vector2((8.5, 4.5))
  @test PhysicsEngine.dot(v1, v2) == -17.5 + 17.5
  @test PhysicsEngine.magnitude(v1) == sqrt(74)
end

@testset "Vector3" begin
  v1 = PhysicsEngine.Vector3((1.0, 5.0, -2.0))
  v2 = PhysicsEngine.Vector3((5.5, -4.0, -0.5))

  @test v1 + v2 == PhysicsEngine.Vector3((6.5, 1.0, -2.5))
  @test v1 - v2 == PhysicsEngine.Vector3((-4.5, 9.0, -1.5))
  @test PhysicsEngine.dot(v1, v2) == 5.5 + -20.0 + 1.0
  @test v1 * v2 == PhysicsEngine.Vector3((-10.5, -10.5, -31.5))
  @test PhysicsEngine.magnitude(v2) == sqrt(46.5)
end

@testset "Vector4" begin
  v1 = PhysicsEngine.Vector4((13, 14, 13, 17))
  v2 = PhysicsEngine.Vector4((3, 4, 5, 6))

  @test v1 + v2 == PhysicsEngine.Vector4((16, 18, 18, 23))
  @test v1 - v2 == PhysicsEngine.Vector4((10, 10, 8, 11))
  @test PhysicsEngine.dot(v1, v2) == 39 + 56 + 65 + 102
  @test PhysicsEngine.magnitude(v2) == sqrt(86)
end

@testset "Matrix" begin
  m1 = PhysicsEngine.Matrix4x4((2, 9, 6, 7, 6, 1, 4, 1, 1, 1, 4, 8, 4, 3, 8, 6))
  m2 = PhysicsEngine.Matrix4x4((6, 7, 9, 3, 4, 6, 3, 9, 3, 9, 8, 4, 8, 5, 9, 4))
  v1 = PhysicsEngine.Vector4((14.0, 24.0, 13.0, 19.0))
  v2 = PhysicsEngine.Vector4((3, 7, 1, 1))

  function isapproxmatrix(x::PhysicsEngine.Matrix4x4, y::PhysicsEngine.Matrix4x4)
    for pair in zip(x, y)
      xValue = pair[1]
      yValue = pair[2]
      if !(xValue ≈ yValue)
        return false
      end
    end
    return true
  end

  @test m1 * m2 == PhysicsEngine.Matrix4x4((122, 157, 156, 139, 60, 89, 98, 47, 86, 89, 116, 60, 108, 148, 163, 95))
  @test m1 * v1 == PhysicsEngine.Vector4((455, 179, 242, 346))
  @test PhysicsEngine.identityMatrix() == PhysicsEngine.Matrix4x4((1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1))
  @test PhysicsEngine.translationMatrix(PhysicsEngine.vec3(2.0, 3.0, -1.0)) == PhysicsEngine.Matrix4x4((1.0, 0.0, 0.0, 2.0, 0.0, 1.0, 0.0, 3.0, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 0.0, 1.0))
  @test PhysicsEngine.translationMatrix(PhysicsEngine.vec3(2.5, -2.5, 4.0)) * v2 == PhysicsEngine.Vector4((5.5, 4.5, 5.0, 1.0))
  @test PhysicsEngine.scalingMatrix(PhysicsEngine.vec3(1.0, 2.0, 0.5)) == PhysicsEngine.Matrix4x4((1.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0))
  @test PhysicsEngine.scalingMatrix(PhysicsEngine.vec3(2.0, -2.0, 5.5)) * v2 == PhysicsEngine.Vector4((6.0, -14.0, 5.5, 1.0))
  @test isapproxmatrix(PhysicsEngine.rotationXMatrix(45.0),  PhysicsEngine.Matrix4x4((1.0, 0.0, 0.0, 0.0, 0.0, cos(-45.0), -sin(-45.0), 0.0, 0.0, sin(-45.0), cos(-45.0), 0.0, 0.0, 0.0, 0.0, 1.0)))
  @test isapproxmatrix(PhysicsEngine.rotationYMatrix(30.0), PhysicsEngine.Matrix4x4((cos(-30.0), 0.0, sin(-30.0), 0.0, 0.0, 1.0, 0.0, 0.0, -sin(-30.0), 0.0, cos(-30.0), 0.0, 0.0, 0.0, 0.0, 1.0)))
  @test isapproxmatrix(PhysicsEngine.rotationZMatrix(22.0), PhysicsEngine.Matrix4x4((cos(-22.0), -sin(-22.0), 0.0, 0.0, sin(-22.0), cos(-22.0), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)))

  #println(PhysicsEngine.invertMatrix(m1))
  #@test isapproxmatrix(PhysicsEngine.invertMatrix(m1))
  # @test rotating vectors
end
