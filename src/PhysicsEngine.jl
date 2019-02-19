module PhysicsEngine

export fullLibraryPath

macro fullLibraryPath()
  return "./src/renderer/libphysicsenginerenderer"
end

include("vector.jl")
include("particle.jl")
include("motion.jl")
include("renderer.jl")
include("controls.jl")
include("simulation.jl")
include("grid.jl")

end # module
