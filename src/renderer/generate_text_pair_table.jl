#!/usr/bin/env julia

using Pkg
Pkg.activate("../../")

using HTTP
using Gumbo
using AbstractTrees

request = HTTP.request("GET", "http://www.unicode.org/reports/tr14/tr14-34.html#PairBasedImplementation")
body = request.body
document = parsehtml(String(body))
pairTable = nothing
for element in PreOrderDFS(document.root)
  if isa(element, HTMLElement)
    if haskey(attrs(element), "class")
      #println(getattr(element, "class"))
      if getattr(element, "class") == "pair"
        global pairTable = element.children[1]
      end
    end
  end
end


function convertBreakOpportunity(opportunity::String)
  map = Dict(
    "^" => "Prohibited",
    "%" => "Indirect",
    "@" => "ProhibitedCM",
    "#" => "IndirectCM",
    "_" => "Direct"
  )

  return map[opportunity]
end


outfile = open("pairtable.h", "w")
println(outfile, """
    #ifndef PAIR_TABLE_H
    #define PAIR_TABLE_H
  """);
println(outfile, """
    typedef enum BreakOpportunity {
      Prohibited,
      Indirect,
      ProhibitedCM,
      IndirectCM,
      Direct
    } BreakOpportunity;
  """);
println(outfile, """
    #define PAIR_TABLE_SIZE 29
    static const BreakOpportunity pairTable[PAIR_TABLE_SIZE][PAIR_TABLE_SIZE] = {
  """);

for row in Iterators.drop(pairTable.children, 1)
  print(outfile, "    {")
  for cell in Iterators.drop(row.children, 1)
    element = cell
    while !isa(element, HTMLText)
      element = element.children[1]
    end
    print(outfile, string(convertBreakOpportunity(element.text)) * ", ")
  end
  println(outfile, "},")
end

println(outfile, """
    };
  """);

println(outfile, """
    #endif
  """);

close(outfile)
