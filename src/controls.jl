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

function space_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  up = Renderer.cameraGetUp(camera)
  up_norm = vec3(up.x * (0.1 / magnitude(up)),
    up.y * (0.1 / magnitude(up)),
    up.z * (0.1 / magnitude(up)))
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + up_norm)
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + up_norm)
end

function rshift_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  up = Renderer.cameraGetUp(camera)
  up_norm = vec3(up.x * (-0.1 / magnitude(up)),
    up.y * (-0.1 / magnitude(up)),
    up.z * (-0.1 / magnitude(up)))
  up_norm = vec3(0.0, -0.1, 0.0)
  Renderer.cameraSetPosition(camera, Renderer.cameraGetPosition(camera) + up_norm)
  Renderer.cameraSetTarget(camera, Renderer.cameraGetTarget(camera) + up_norm)
end

theta = 0.0

function leftarrow_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  global theta = theta + 0.02
  new_direction = vec3(sin(theta), 0.0, cos(theta))
  Renderer.cameraSetTarget(camera, Renderer.cameraGetPosition(camera) + new_direction)
end

function rightarrow_pressed(renderer, key)
  camera = Renderer.getCamera(renderer)
  global theta = theta - 0.02
  new_direction = vec3(sin(theta), 0.0, cos(theta))
  Renderer.cameraSetTarget(camera, Renderer.cameraGetPosition(camera) + new_direction)
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

  Renderer.addKeyCallback(renderer, space_pressed, Renderer.Space, Renderer.Press)
  Renderer.addKeyCallback(renderer, space_pressed, Renderer.Space, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, rshift_pressed, Renderer.RightShift, Renderer.Press)
  Renderer.addKeyCallback(renderer, rshift_pressed, Renderer.RightShift, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, leftarrow_pressed, Renderer.KeyLeft, Renderer.Press)
  Renderer.addKeyCallback(renderer, leftarrow_pressed, Renderer.KeyLeft, Renderer.Repeat)

  Renderer.addKeyCallback(renderer, rightarrow_pressed, Renderer.KeyRight, Renderer.Press)
  Renderer.addKeyCallback(renderer, rightarrow_pressed, Renderer.KeyRight, Renderer.Repeat)
end
