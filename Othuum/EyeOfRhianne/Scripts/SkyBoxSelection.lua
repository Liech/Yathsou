local inspect = require 'Data.lua.inspect'

print("Current SkyBox Is: ");
print(inspect(eyeGetSkyBox()));
print("List of All SkyBox:");
print(inspect(eyeGetAllSkyBox()));
print("Set SkyBox to SkyCube_Evergreen03a.dds");
eyeSetSkyBox("SkyCube_Evergreen03a.dds");

eyeDisableSkyBox();
eyeSetSkyBoxColor({0,255,0,128});