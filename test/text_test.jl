import PhysicsEngine

using HTTP

@testset "Line Breaking" begin
  request = HTTP.request("GET", "http://www.unicode.org/Public/UCD/latest/ucd/auxiliary/LineBreakTest.txt")
  body = String(request.body)
  working = true
  line_n = 1
  for line in split(body, '\n')
    main_string = split(line, '#')[1]
    tokens = split(main_string)
    breaks = UInt32[]
    seq = ""
    skip = false
    for token in tokens
      if token == "×"
        push!(breaks, UInt32(1))
      elseif token == "÷"
        push!(breaks, UInt32(0))
      else
        if parse(UInt32, token, base=16) > 128
          skip = true
        end
        seq = seq * string(Char(parse(UInt32, token, base=16)))
      end
    end

    if skip
      line_n += 1
      continue
    end

    generatedBreaksPtr = ccall((:lineBreaks, PhysicsEngine.@fullLibraryPath), Ptr{UInt32}, (Cstring,), seq)
    generatedBreaks = UInt32[]
    # Make an array
    for i = 1:(length(seq) + 1)
      action = Base.unsafe_load(generatedBreaksPtr, i)
      if action == 2
        action = 0
      end
      push!(generatedBreaks, UInt32(action))
    end

    broken = false
    for (expected, actual) in zip(breaks, generatedBreaks)
      if expected != actual
        broken = true
        working = false
      end
    end

    if broken
      print("$line_n - ")
      index = 1
      for c in seq
        ex = breaks[index]
        ac = generatedBreaks[index]
        print(" [$ex|$ac] ")
        print(UInt32(c))
        print("('$c')")
        print(" ")
        index += 1
      end
      ex = breaks[index]
      ac = breaks[index]
      print(" [$ex|$ac]")
      print("\n")
    end
    line_n += 1
  end
  @test working == true
end
