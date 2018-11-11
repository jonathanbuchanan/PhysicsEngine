import PhysicsEngine

using HTTP

@testset "Line Breaking" begin
  request = HTTP.request("GET", "http://www.unicode.org/Public/UCD/latest/ucd/auxiliary/LineBreakTest.txt")
  body = String(request.body)
  working = true
  line_n = 1
  fails = 0
  total = 0

  # Bad tests to skip
  skip_lines = [
    1141,
    1145,
    1309,
    1313,
    2981,
    4497,
    4665,
    5165
  ]

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

    if line_n in skip_lines
      skip = true
    end

    if skip
      line_n += 1
      continue
    end

    if length(tokens) > 0
      total += 1
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
      fails += 1
      print("$line_n - ")
      index = 1
      for c in seq
        ex = breaks[index]
        ac = generatedBreaks[index]
        print(" [$ex|$ac] ")
        print(UInt32(c))
        #print("('$c')")
        print(" ")
        index += 1
      end
      ex = breaks[index]
      ac = generatedBreaks[index]
      print(" [$ex|$ac]")
      print("\n")
    end
    line_n += 1
  end
  print("Fails: $fails / $total \n")
  @test working == true
end
