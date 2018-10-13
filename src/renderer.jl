module Renderer

const libPath = "./src/renderer/libphysicsenginerenderer"

function fullLibPath()
  return libPath * libName
end


# Bindings

# Main
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

function terminate()
  ccall((:terminate, libPath), Cvoid, ())
end


# Render
const RenderInfo = Ptr{Cvoid}

function createRenderer(window::Window)
  ccall((:createRenderer, libPath), RenderInfo, (Window,), window)
end

function render(window::Window, renderer::RenderInfo)
  ccall((:render, libPath), Cvoid, (Window, RenderInfo), window, renderer)
end

function clear(window::Window)
  ccall((:clear, libPath), Cvoid, (Window,), window)
end

function swapBuffers(window::Window)
  ccall((:swapBuffers, libPath), Cvoid, (Window,), window)
end

function setClearColor(window::Window, red::Float64, green::Float64, blue::Float64, alpha::Float64)
  ccall((:setClearColor, libPath), Cvoid, (Window, Cfloat, Cfloat, Cfloat, Cfloat), window, red, green, blue, alpha)
end


end
