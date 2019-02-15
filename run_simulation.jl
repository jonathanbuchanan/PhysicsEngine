#!/usr/bin/env julia

using Pkg
Pkg.activate(".")
using PhysicsEngine

PhysicsEngine.simulate()
