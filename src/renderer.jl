module Renderer

const libPath = "./src/renderer/libphysicsenginerenderer"

function fullLibPath()
  return libPath * libName
end


# Bindings
const Window = Ptr{Cvoid}

function init()
  return ccall((:init, libPath), Int32, ())
end

function createWindow(width::Int, height::Int, title::String)
  return ccall((:createWindow, libPath), Cvoid, (Int32, Int32, Cstring), width, height, title)
end

function terminate()
  return ccall((:terminate, libPath), Int32, ())
end

end
