local inspect = require 'Data.lua.inspect'


local allUnitIDs = eyeGetAllUnits();

for key, value in pairs(allUnitIDs) do
    print(key, " -- ", value)

    eyeSetUnit(value);
    local bp = eyeGetBlueprint(value)
	print("BP" .. type(bp))
	if type(bp) ~= "string" then
      local nameWithTranslation = bp["General"]["UnitName"];
    local name = value;
	  if nameWithTranslation ~= nil then
        name = string.gmatch(nameWithTranslation,'.*>(.*)')(1)
        name = name:gsub("%\"", "");
        print(name)
    end
    eyeSaveScreenshot("screenshots/" .. name .. ".png");
	end
end
