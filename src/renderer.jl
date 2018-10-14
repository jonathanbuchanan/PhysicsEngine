module Renderer

import ..@fullLibraryPath

# Bindings

# Main
const Window = Ptr{Cvoid}

function init()
  return ccall((:init, @fullLibraryPath), Int32, ())
end

function createWindow(width::Int, height::Int, title::String)
  return ccall((:createWindow, @fullLibraryPath), Window, (Int32, Int32, Cstring), width, height, title)
end

function windowCloseStatus(window::Window)
  return ccall((:windowCloseStatus, @fullLibraryPath), Bool, (Window,), window)
end

function terminate()
  ccall((:terminate, @fullLibraryPath), Cvoid, ())
end


# Render
const RenderInfo = Ptr{Cvoid}

#mutable struct Camera
#  position::Vector3
#end

function createRenderer(window::Window)
  ccall((:createRenderer, @fullLibraryPath), RenderInfo, (Window,), window)
end

function render(window::Window, renderer::RenderInfo)
  ccall((:render, @fullLibraryPath), Cvoid, (Window, RenderInfo), window, renderer)
end

function clear(window::Window)
  ccall((:clear, @fullLibraryPath), Cvoid, (Window,), window)
end

function swapBuffers(window::Window)
  ccall((:swapBuffers, @fullLibraryPath), Cvoid, (Window,), window)
end

function setClearColor(window::Window, red::Float64, green::Float64, blue::Float64, alpha::Float64)
  ccall((:setClearColor, @fullLibraryPath), Cvoid, (Window, Cfloat, Cfloat, Cfloat, Cfloat), window, red, green, blue, alpha)
end


end
