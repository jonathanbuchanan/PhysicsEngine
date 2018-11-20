function w_pressed(key)
  print("w\n")
end

function a_pressed(key)
  print("a\n")
end

function s_pressed(key)
  print("s\n")
end

function d_pressed(key)
  print("d\n")
end

function registerControls(renderer, camera)
  Renderer.addKeyCallback(renderer, w_pressed, Renderer.KeyW, Renderer.Press)
  Renderer.addKeyCallback(renderer, a_pressed, Renderer.KeyA, Renderer.Press)
  Renderer.addKeyCallback(renderer, s_pressed, Renderer.KeyS, Renderer.Press)
  Renderer.addKeyCallback(renderer, d_pressed, Renderer.KeyD, Renderer.Press)
end
