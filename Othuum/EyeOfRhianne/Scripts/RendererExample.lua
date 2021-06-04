local inspect = require 'Data.lua.inspect'

print("Current Renderer Is: ");
print(inspect(eyeGetRenderer()));
print("List of All Renderer:");
print(inspect(eyeGetAllRenderer()));
print("Set Renderer to gNormal");
eyeSetRenderer("gNormal");

print("Set Renderer to gSpecial");
eyeSetRenderer("gSpecial");
--gSpecial.red = reflection;
--gSpecial.green = glow;
--gSpecial.blue = specular;