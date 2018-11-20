function w_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  forward = Renderer.cameraGetTarget(camera) - Renderer.cameraGetPosition(camera)
  forward_norm = vec3(forward.x * (0.1 / magnitude(forward)),
    forward.y * (0.1 / magnitude(forward)),
    forward.z * (0.1 / magnitude(forward)))
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + (forward_norm))
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + (forward_norm))
  return
end

function a_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  forward = Renderer.cameraGetTarget(camera) - Renderer.cameraGetPosition(camera)
  forward_norm = vec3(forward.x * (1 / magnitude(forward)),
    forward.y * (1 / magnitude(forward)),
    forward.z * (1 / magnitude(forward)))

  up = Renderer.cameraGetUp(camera)
  up_norm = vec3(up.x * (1 / magnitude(up)),
    up.y * (1 / magnitude(up)),
    up.z * (1 / magnitude(up)))

  left = up * forward
  left_norm = vec3(left.x * (0.1 / magnitude(left)),
    left.y * (0.1 / magnitude(left)),
    left.z * (0.1 / magnitude(left)))
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + left_norm)
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + left_norm)
  return
end

function s_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  forward = Renderer.cameraGetTarget(camera) - Renderer.cameraGetPosition(camera)
  forward_norm = vec3(forward.x * (-0.1 / magnitude(forward)),
    forward.y * (-0.1 / magnitude(forward)),
    forward.z * (-0.1 / magnitude(forward)))
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + (forward_norm))
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + (forward_norm))
  return
end

function d_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  forward = Renderer.cameraGetTarget(camera) - Renderer.cameraGetPosition(camera)
  forward_norm = vec3(forward.x * (1 / magnitude(forward)),
    forward.y * (1 / magnitude(forward)),
    forward.z * (1 / magnitude(forward)))

  up = Renderer.cameraGetUp(camera)
  up_norm = vec3(up.x * (1 / magnitude(up)),
    up.y * (1 / magnitude(up)),
    up.z * (1 / magnitude(up)))

  left = forward * up
  left_norm = vec3(left.x * (0.1 / magnitude(left)),
    left.y * (0.1 / magnitude(left)),
    left.z * (0.1 / magnitude(left)))
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + left_norm)
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + left_norm)
  return
end

function registerControls(renderer, camera)
  Renderer.addKeyCallback(renderer, w_pressed, Renderer.KeyW, Renderer.Press)
  Renderer.addKeyCallback(renderer, w_pressed, Renderer.KeyW, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, a_pressed, Renderer.KeyA, Renderer.Press)
  Renderer.addKeyCallback(renderer, a_pressed, Renderer.KeyA, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, s_pressed, Renderer.KeyS, Renderer.Press)
  Renderer.addKeyCallback(renderer, s_pressed, Renderer.KeyS, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, d_pressed, Renderer.KeyD, Renderer.Press)
  Renderer.addKeyCallback(renderer, d_pressed, Renderer.KeyD, Renderer.Repeat)
end
