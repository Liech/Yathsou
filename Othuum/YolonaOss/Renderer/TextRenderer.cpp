#include "TextRenderer.h"

#include "structs/Factory.h"

Factory<Drawable>::Registrator<TextRenderer> RegisterTextRenderer("TextRenderer", {"PreDrawCall"});