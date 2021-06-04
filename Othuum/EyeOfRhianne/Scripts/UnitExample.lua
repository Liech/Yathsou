local inspect = require 'Data.lua.inspect'

print("Current Unit Is: ");
print(inspect(eyeGetUnit()));
print("List of All Unit:");
print(inspect(eyeGetAllUnits()));
print("Set Unit to galactic collosus");
eyeSetUnit("UAL0401");


print(inspect(eyeGetBlueprint("UAL0401")));
print("Faction is " .. eyeGetBlueprint("UAL0401")["General"]["FactionName"]);
local nameWithTranslation = eyeGetBlueprint("UAL0401")["General"]["UnitName"];
local name = string.gmatch(nameWithTranslation,'.*>(.*)')(1)
print("Name is " .. name)

eyeSetUnitColor({255,0,0,255});