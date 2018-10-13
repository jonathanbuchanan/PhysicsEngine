module Renderer

const libName = "libphysicsenginerenderer"
const libPath = "./src/renderer/"

function fullLibPath()
  return libPath * libName
end

function test()
  return ccall((:test, "./src/renderer/libphysicsenginerenderer"), Int32, ())
end

end
