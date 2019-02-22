# This file contains all linear algebra code
# All functions are defined and called from the C library for interoperability


# Vector2
const Vector2 = NamedTuple{(:x, :y), Tuple{Float64, Float64}}

function vec2(x::Float64, y::Float64)
  return Vector2((x, y))
end

function Base.:+(a::Vector2, b::Vector2)
  return ccall((:addVector2, @fullLibraryPath), Vector2, (Vector2, Vector2), a, b)
end

function Base.:-(a::Vector2, b::Vector2)
  return ccall((:subtractVector2, @fullLibraryPath), Vector2, (Vector2, Vector2), a, b)
end

function dot(a::Vector2, b::Vector2)
  return ccall((:dotProduct2, @fullLibraryPath), Cdouble, (Vector2, Vector2), a, b)
end

function magnitude(v::Vector2)
  return ccall((:magnitudeVector2, @fullLibraryPath), Cdouble, (Vector2,), v)
end

# Vector3
const Vector3 = NamedTuple{(:x, :y, :z), Tuple{Float64, Float64, Float64}}

function vec3(x::Float64, y::Float64, z::Float64)
  return Vector3((x, y, z))
end

function Base.:+(a::Vector3, b::Vector3)
  return ccall((:addVector3, @fullLibraryPath), Vector3, (Vector3, Vector3), a, b)
end

function Base.:-(a::Vector3, b::Vector3)
  return ccall((:subtractVector3, @fullLibraryPath), Vector3, (Vector3, Vector3), a, b)
end

function dot(a::Vector3, b::Vector3)
  return ccall((:dotProduct, @fullLibraryPath), Cdouble, (Vector3, Vector3), a, b)
end

function Base.:*(a::Vector3, b::Vector3)
  return ccall((:crossProduct, @fullLibraryPath), Vector3, (Vector3, Vector3), a, b)
end

function magnitude(v::Vector3)
  return ccall((:magnitudeVector3, @fullLibraryPath), Cdouble, (Vector3,), v)
end

# Vector4
const Vector4 = NamedTuple{(:x, :y, :z, :w), Tuple{Float64, Float64, Float64, Float64}}

function vec4(x::Float64, y::Float64, z::Float64, w::Float64)
  return Vector4((x, y, z, w))
end

function Base.:+(a::Vector4, b::Vector4)
  return ccall((:addVector4, @fullLibraryPath), Vector4, (Vector4, Vector4), a, b)
end

function Base.:-(a::Vector4, b::Vector4)
  return ccall((:subtractVector4, @fullLibraryPath), Vector4, (Vector4, Vector4), a, b)
end

function dot(a::Vector4, b::Vector4)
  return ccall((:dotProduct4, @fullLibraryPath), Cdouble, (Vector4, Vector4), a, b)
end

function magnitude(v::Vector4)
  return ccall((:magnitudeVector4, @fullLibraryPath), Cdouble, (Vector4,), v)
end

# Matrices
const Matrix4x4 = NamedTuple{(:a11, :a12, :a13, :a14, :a21, :a22, :a23, :a24, :a31, :a32, :a33, :a34, :a41, :a42, :a43, :a44),
  Tuple{Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64, Float64}}

function Base.:*(a::Matrix4x4, b::Matrix4x4)
  return ccall((:multiplyMatrix4x4, @fullLibraryPath), Matrix4x4, (Matrix4x4, Matrix4x4), a, b)
end

function identityMatrix()
  return ccall((:identityMatrix4x4, @fullLibraryPath), Matrix4x4, ())
end

function translationMatrix(translation::Vector3)
  return ccall((:translationMatrix, @fullLibraryPath), Matrix4x4, (Vector3,), translation)
end

function scalingMatrix(scale::Vector3)
  return ccall((:scalingMatrix, @fullLibraryPath), Matrix4x4, (Vector3,), scale)
end

function rotationXMatrix(angle::Float64)
  return ccall((:rotationXMatrix, @fullLibraryPath), Matrix4x4, (Cdouble,), angle)
end

function rotationYMatrix(angle::Float64)
  return ccall((:rotationYMatrix, @fullLibraryPath), Matrix4x4, (Cdouble,), angle)
end

function rotationZMatrix(angle::Float64)
  return ccall((:rotationZMatrix, @fullLibraryPath), Matrix4x4, (Cdouble,), angle)
end

function Base.:*(a::Matrix4x4, b::Vector4)
  return ccall((:matrix4x4timesVector4, @fullLibraryPath), Vector4, (Matrix4x4, Vector4), a, b)
end

function perspective(zNear::Float64, zFar::Float64, fovy::Float64, aspect::Float64)
  return ccall((:perspectiveProjectionMatrix, @fullLibraryPath), Matrix4x4, (Float64, Float64, Float64, Float64), zNear, zFar, fovy, aspect)
end
