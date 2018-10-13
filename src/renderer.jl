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
  return ccall((:createWindow, libPath), Window, (Int32, Int32, Cstring), width, height, title)
end

function windowCloseStatus(window::Window)
  return ccall((:windowCloseStatus, libPath), Bool, (Window,), window)
end

function render(window::Window)
  ccall((:render, libPath), Cvoid, (Window,), window)
end

function terminate()
  ccall((:terminate, libPath), Cvoid, ())
end

end
