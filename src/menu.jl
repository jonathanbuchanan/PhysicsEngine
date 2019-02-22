const Menu = Ptr{Cvoid}
const Label = Ptr{Cvoid}
const Button = Ptr{Cvoid}

@enum MenuOrientation begin
  Vertical = 0
  Horizontal = 1
  Central = 2
end

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

function createLabel()
  ccall((:createLabel, @fullLibraryPath), Label, ())
end

function createButton()
  ccall((:createButton, @fullLibraryPath), Button, ())
end
