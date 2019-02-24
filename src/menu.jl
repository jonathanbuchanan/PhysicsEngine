const Menu = Ptr{Cvoid}
const Control = Ptr{Cvoid}
const Label = Ptr{Cvoid}
const Button = Ptr{Cvoid}

@enum MenuOrientation begin
  Vertical = 0
  Horizontal = 1
  Central = 2
end

# Menu
function createMenu()
  ccall((:createMenu, @fullLibraryPath), Menu, ())
end

function setMenuOrientation(menu, orientation)
  ccall((:setMenuOrientation, @fullLibraryPath), Cvoid, (Menu, MenuOrientation), menu, orientation)
end

function setMenuPosition(menu, position)
  ccall((:setMenuPosition, @fullLibraryPath), Cvoid, (Menu, Vector2), menu, position)
end

function setMenuSize(menu, size)
  ccall((:setMenuSize, @fullLibraryPath), Cvoid, (Menu, Vector2), menu, size)
end

function setMenuColor(menu, color)
  ccall((:setMenuColor, @fullLibraryPath), Cvoid, (Menu, Vector4), menu, color)
end

function addControlToMenu(menu, control)
  ccall((:addControlToMenu, @fullLibraryPath), Cvoid, (Menu, Control), menu, control)
end

# Label
function createLabel()
  ccall((:createLabel, @fullLibraryPath), Label, ())
end

function setLabelZ(label, z)
  ccall((:setLabelZ, @fullLibraryPath), Cvoid, (Label, Cint), label, z)
end

function setLabelPosition(label, position)
  ccall((:setLabelPosition, @fullLibraryPath), Cvoid, (Label, Vector2), label, position)
end

function setLabelSize(label, size)
  ccall((:setLabelSize, @fullLibraryPath), Cvoid, (Label, Vector2), label, size)
end

function setLabelColor(label, color)
  ccall((:setLabelColor, @fullLibraryPath), Cvoid, (Label, Vector4), label, color)
end

function setLabelTextHeight(label, textHeight)
  ccall((:setLabelTextHeight, @fullLibraryPath), Cvoid, (Label, Cint), label, textHeight)
end

function setLabelText(label, text)
  ccall((:setLabelText, @fullLibraryPath), Cvoid, (Label, Cstring), label, text)
end

# Button
function createButton()
  ccall((:createButton, @fullLibraryPath), Button, ())
end
