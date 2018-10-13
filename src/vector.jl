# All vector/transformation code lives here
const Vector3 = NamedTuple{(:x, :y, :z), Tuple{Float64, Float64, Float64}}

function vec3(x::Float64, y::Float64, z::Float64)
  return Vector3((x, y, z))
end

function Base.:+(a::Vector3, b::Vector3)
  return vec3(a.x + b.x, a.y + b.y, a.z + b.z)
end

function Base.:-(a::Vector3, b::Vector3)
  return vec3(a.x - b.x, a.y - b.y, a.z - b.z)
end

function dot(a::Vector3, b::Vector3)
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z)
end

function Base.:*(a::Vector3, b::Vector3)
  return vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x))
end
