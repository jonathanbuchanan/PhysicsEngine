module Renderer

import ..@fullLibraryPath
import ..Vector3

# Bindings

const Window = Ptr{Cvoid}
const RenderInfo = Ptr{Cvoid}

function init()
  return ccall((:init, @fullLibraryPath), Int32, ())
end

function createWindow(width::Int, height::Int, title::String)
  return ccall((:createWindow, @fullLibraryPath), Window, (Int32, Int32, Cstring), width, height, title)
end

function windowCloseStatus(window::Window)
  return ccall((:windowCloseStatus, @fullLibraryPath), Bool, (Window,), window)
end

function closeWindow(window::Window)
  return ccall((:closeWindow, @fullLibraryPath), Cvoid, (Window,), window)
end

function terminate(renderer::RenderInfo)
  ccall((:terminate, @fullLibraryPath), Cvoid, (RenderInfo,), renderer)
end

function createRenderer(window::Window)
  ccall((:createRenderer, @fullLibraryPath), RenderInfo, (Window,), window)
end

function render(renderer::RenderInfo)
  ccall((:render, @fullLibraryPath), Cvoid, (RenderInfo,), renderer)
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

function addKeyCallback(renderer::RenderInfo, callback, key, action)
  ccall((:addKeyCallback, @fullLibraryPath), Cvoid, (RenderInfo, Cint, Cint, Ptr{Cvoid}), renderer, key, action, @cfunction($callback, Cvoid, (Cint,)))
end

@enum Key begin
  Unknown = -1
  Space = 32
  Apostrophe = 39
  Comma = 44
  Minus = 45
  Period = 46
  Slash = 47
  Key0 = 48
  Key1 = 49
  Key2 = 50
  Key3 = 51
  Key4 = 52
  Key5 = 53
  Key6 = 54
  Key7 = 55
  Key8 = 56
  Key9 = 57
  Semicolon = 59
  Equal = 61
  KeyA = 65
  KeyB = 66
  KeyC = 67
  KeyD = 68
  KeyE = 69
  KeyF = 70
  KeyG = 71
  KeyH = 72
  KeyI = 73
  KeyJ = 74
  KeyK = 75
  KeyL = 76
  KeyM = 77
  KeyN = 78
  KeyO = 79
  KeyP = 80
  KeyQ = 81
  KeyR = 82
  KeyS = 83
  KeyT = 84
  KeyU = 85
  KeyV = 86
  KeyW = 87
  KeyX = 88
  KeyY = 89
  KeyZ = 90
  LeftBracket = 91
  Backslash = 92
  RightBracket = 93
  GraveAccent = 96
  World1 = 161
  World2 = 162
  Escape = 256
  Enter = 257
  Tab = 258
  Backspace = 259
  Insert = 260
  Delete = 261
  KeyRight = 262
  KeyLeft = 263
  KeyDown = 264
  KeyUp = 265
  PageUp = 266
  PageDown = 267
  KeyHome = 268
  KeyEnd = 269
  KeyCapsLock = 280
  KeyScrollLock = 281
  KeyNumLock = 282
  KeyPrintScreen = 283
  KeyPause = 284
  KeyF1 = 290
  KeyF2 = 291
  KeyF3 = 292
  KeyF4 = 293
  KeyF5 = 294
  KeyF6 = 295
  KeyF7 = 296
  KeyF8 = 297
  KeyF9 = 298
  KeyF10 = 299
  KeyF11 = 300
  KeyF12 = 301
  KeyF13 = 302
  KeyF14 = 303
  KeyF15 = 304
  KeyF16 = 305
  KeyF17 = 306
  KeyF18 = 307
  KeyF19 = 308
  KeyF20 = 209
  KeyF21 = 310
  KeyF22 = 311
  KeyF23 = 312
  KeyF24 = 313
  KeyF25 = 314
  KeyPad0 = 320
  KeyPad1 = 321
  KeyPad2 = 322
  KeyPad3 = 323
  KeyPad4 = 324
  KeyPad5 = 325
  KeyPad6 = 326
  KeyPad7 = 327
  KeyPad8 = 328
  KeyPad9 = 329
  KeyPadDecimal = 330
  KeyPadDivide = 331
  KeyPadMultiply = 332
  KeyPadSubtract = 333
  KeyPadAdd = 334
  KeyPadEnter = 335
  KeyPadEqual = 336
  LeftShift = 340
  LeftControl = 341
  LeftAlt = 342
  LeftSuper = 343
  RightShift = 344
  RightControl = 345
  RightAlt = 346
  RightSuper = 347
  KeyMenu = 348
end

@enum KeyAction begin
  Release = 0
  Press = 1
  Repeat = 2
end

const Camera = Ptr{Cvoid}

function getCamera(renderer::RenderInfo)
  return ccall((:getCamera, @fullLibraryPath), Camera, (RenderInfo,), renderer)
end

function cameraGetPosition(camera::Camera)
  return ccall((:cameraGetPosition, @fullLibraryPath), Vector3, (Camera,), camera)
end

function cameraGetTarget(camera::Camera)
  return ccall((:cameraGetTarget, @fullLibraryPath), Vector3, (Camera,), camera)
end

function cameraGetUp(camera::Camera)
  return ccall((:cameraGetUp, @fullLibraryPath), Vector3, (Camera,), camera)
end

function cameraSetPosition(camera::Camera, position::Vector3)
  return ccall((:cameraSetPosition, @fullLibraryPath), Cvoid, (Camera, Vector3), camera, position)
end

function cameraSetTarget(camera::Camera, target::Vector3)
  return ccall((:cameraSetTarget, @fullLibraryPath), Cvoid, (Camera, Vector3), camera, target)
end

function cameraSetUp(camera::Camera, up::Vector3)
  return ccall((:cameraSetUp, @fullLibraryPath), Cvoid, (Camera, Vector3), camera, up)
end

end
